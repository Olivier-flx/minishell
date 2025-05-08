/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 10:30:25 by ofilloux          #+#    #+#             */
/*   Updated: 2025/05/08 20:11:23 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void redirect_input_file(t_data *data, t_exe *exe, t_chunk *chunk)
{
	if (chunk->has_here_doc)
		listen_heredocs(chunk);
	if(ft_strcmp(chunk->tokens[0], "<") == 0)
	{
		chunk->input_file_fd[0] = open(chunk->input_redir_file[0], O_RDONLY);
		if (chunk->input_file_fd[0] < 0)
		{
			strerror(errno);
			clean_cmds_exit(data, EXIT_FAILURE/* , "Err opening input file\n" */);// @confirm
		}
		chunk->input_file_open[0] = true;

		if (dup2(chunk->input_file_fd[0], STDIN_FILENO) == -1)
		{
			strerror(errno);
			clean_cmds_exit(data, EXIT_FAILURE/* , "Err dup2 : input file\n" */);// @confirm
		}
		close(chunk->input_file_fd[0]);
		chunk->input_file_open[0] = false;
	}
	// if (dup2(files[0].fd, STDIN_FILENO) == -1)
	// 	clean_cmds_exit(cmd, EXIT_FAILURE, "Err dup2 : input file\n");
	// close(files[0].fd);
	//files[0].file_open = false;
}

void redirect_to_output_file(t_data *data, t_exe *exe, t_chunk *chunk)
{
	// files[1].fd = open(files[1].name, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR
	// 	| S_IWUSR | S_IRGRP | S_IROTH);
	// if (files[1].fd < 0)
	// 	clean_cmds_exit(cmd, EXIT_FAILURE, "Err opening output file\n");
	if (chunk->redir_file_count > 0)
	{
		if (dup2(chunk->file_fd[chunk->redir_file_count - 1], STDOUT_FILENO) == -1)
		{
			strerror(errno);
			clean_cmds_exit(data, EXIT_FAILURE/* , "Error dup2 : last cmd\n" */);
		}
		close(chunk->file_fd[chunk->redir_file_count - 1]); //@optimize : peut etre rendu plus robust avec strerror et errno
	}
}

void close_unecessary_pipes(t_exe *exe, int i)
{
	int j;

	j = 0;
	while (j < exe->total_cmd_count - 1)
	{
		if (j != i && close(exe->pipe_arr[j][0]) == -1){
			printf("(*pipe_arr)[j][0] --> j == %d\n", j); // @confirm : dois-je gerer ainsi ?
			//perror("Error closing pipe_arr[j][0]");
			}
		if (j != i + 1 && close(exe->pipe_arr[j][1])){
			printf("(*pipe_arr)[j][1] --> j == %d\n", j);// @confirm : dois-je gerer ainsi ?
			//perror("Error closing pipe_arr[j][1]");
			}
		j++;
	}
}


void	run_cmd(t_data *data, t_exe *exe, t_chunk *chunk, int i)
{
	close_unecessary_pipes(exe, i - 1);
	redirect_input_file(data, exe, chunk);
	redirect_to_output_file(data, exe, chunk);
	if (i > 0 && dup2(exe->pipe_arr[i - 1][0], STDIN_FILENO) == -1)
		clean_cmds_exit(data, EXIT_FAILURE/* , "Err dup2 : i > 0 ; fd[0]\n" */);
	if (i >= 0 && i < exe->total_cmd_count - 1)
		close(exe->pipe_arr[i][0]);
	if (i < exe->total_cmd_count - 1 && dup2(exe->pipe_arr[i][1], STDOUT_FILENO) == -1)
		clean_cmds_exit(data, EXIT_FAILURE/* , "Err dup2 : i > cmd-1 ; fd[1]\n" */);
	if (i < exe->total_cmd_count - 1)
		close(exe->pipe_arr[i][1]);
	if (execve(chunk->argv[0], chunk->argv, data->env) == -1)
	{
		clean_cmds_exit(data, EXIT_FAILURE/* , "Error executing first cmd\n" */);
		exit(EXIT_FAILURE);// quitte juste le sous process
	}
}

static void	waiting_childs(t_exe *exe, int *pid_arr)
{
	int i;

	i = 0;
	while (i < exe->valid_cmd_count)
	 {
		//if (cmd->cmd_is_valid_arr[i] == true)
		waitpid(pid_arr[i], NULL, 0);
		i++;
	 }
}

static void close_all_pipes(t_exe *exe, int ***pipe_arr)
{
	int	j;

	j = 0;
	while (j < exe->total_cmd_count - 1)
	{
		if (close((*pipe_arr)[j][0]) == -1)
			perror("Err close_all_pipes [j][0]");
		if (close((*pipe_arr)[j][1]) == -1)
			perror("Err close_all_pipes [j][1]");
		j++;
	}
}

void	init_pid_arr(t_data *data, t_exe *exe)
{
	int i;

	i = 0;
	exe->pid_arr = malloc(exe->valid_cmd_count * sizeof(int));
	if (!exe->pid_arr)
		clean_cmds_exit(data, EXIT_FAILURE/* , "Malloc err pid_arr" */); //@optimize, normalement dans pipex, cela supprimer faisait un exit, donc la suite du program n'etait pas execute. Ici ce n'est plus le cas, il faut donc gerer differament pour etre sur de ne pas avoir des free multiples etc;
	exe->pid_arr_malloced = true;
	while (i < exe->valid_cmd_count)
		exe->pid_arr[i++] = -2;
}

void	init_pipes_2arr(t_data *data, t_exe *exe)
{
	int i;

	exe->pipe_arr = malloc(sizeof(int *) * (exe->total_cmd_count - 1));
	if (!exe->pipe_arr)
		clean_cmds_exit(data, EXIT_FAILURE/* , "Malloc err pipes" */);
	exe->pipe_arr_malloced = true;
	i = 0;
	while (i < exe->total_cmd_count - 1)
	{
		exe->pipe_arr[i] = malloc(sizeof(int) * 2);
		if (!exe->pipe_arr[i])
			clean_cmds_exit(data, EXIT_FAILURE/* , "Malloc err pipe_arr[i]" */); //@optimize, same as before and // pourrait rendre plus robuste si erreur de malloc
		exe->pipes_malloced[i] = true;
		if (pipe(exe->pipe_arr[i]) == -1)
			clean_cmds_exit(data, EXIT_FAILURE/* , "Error in pipe : run_pipex" */); //@optimize, same as before
		i++;
	}
}

void	run_pipex(t_data *data)
{
	int		i;
	t_dlist	*i_node;

	init_pid_arr(data, &data->exec_info);
	init_pipes_2arr(data , &data->exec_info);
	i = 0;
	i_node = data->cmd_list;
	while (i < data->exec_info.valid_cmd_count/*  cmd->cmd_count */)
	{
		/* if (cmd->cmd_is_valid_arr[i] == false)
		{
			invalid_cmd++;
			i++;
			continue ;
		} */
		if (i_node && ((t_chunk *)i_node->content)->type != CMD)
		{
			i_node = i_node->next;
			continue ;
		}
		if (data->exec_info.cmd_is_valid_arr[i] == true)
		{
			data->exec_info.pid_arr[i] = fork();
			if (data->exec_info.pid_arr[i] == -1)
				clean_cmds_exit(data, EXIT_FAILURE/* , "Error in forking: run_pipex" */);
			if (data->exec_info.pid_arr[i] == 0)
				run_cmd (data, &data->exec_info, ((t_chunk *)i_node->content), i);
		}
		i++;
	}
	close_all_pipes(&data->exec_info, &data->exec_info.pipe_arr);
	waiting_childs(&data->exec_info, data->exec_info.pid_arr);
}


int main_exec(t_data *data)
{
	//t_dlist *i_node;

	//expend_all(data);
	init_files(data); // OK for now
	init_cmd(data);
	run_pipex(data);
	clean_cmds_exit(data, EXIT_SUCCESS);

	/* i_node = data->cmd_list;
	while (i_node)
	{
		ft_echo(data->env_list, ((t_chunk *)(i_node->content))->argv);
		i_node = i_node->next;
	} */
	return(SUCCESS);
}
