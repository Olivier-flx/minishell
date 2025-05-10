/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 10:30:25 by ofilloux          #+#    #+#             */
/*   Updated: 2025/05/10 19:00:01 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void redirect_input_file(t_data *data, t_chunk *chunk)
{
	int	i;

	i = 0;
	if (!data)
		return;
	while (chunk->input_redir && chunk->input_redir[i])
	{
		if (chunk->has_here_doc)
			listen_heredocs(chunk, i);
		if(ft_strcmp(chunk->input_redir[i], "<") == 0)
		{
			chunk->input_file_fd[i] = open(chunk->input_redir_file[i], O_RDONLY);
			if (chunk->input_file_fd[0] < 0)
				strerror(errno); // @optimize
			chunk->input_file_open[0] = true;
			if (dup2(chunk->input_file_fd[i], STDIN_FILENO) == -1)
				strerror(errno); // @optimize
			close(chunk->input_file_fd[i]);
			chunk->input_file_open[i] = false;
		}
		i++;
	}
	// if (dup2(files[0].fd, STDIN_FILENO) == -1)
	// 	clean_cmds_exit(cmd, EXIT_FAILURE, "Err dup2 : input file\n");
	// close(files[0].fd);
	//files[0].file_open = false;
}

void redirect_to_output_file(t_data *data, t_chunk *chunk)
{
	if (chunk->redir_file_count > 0)
	{
		chunk->file_fd[chunk->redir_file_count - 1] = open(chunk->redir_files[chunk->redir_file_count - 1], O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR
			| S_IWUSR | S_IRGRP | S_IROTH);
		if (chunk->file_fd[chunk->redir_file_count - 1] < 0)
			strerror(errno); // @optimize
		if (!data)
			return;
		printf(" output file : %s, file fd = %i\n", chunk->redir_files[chunk->redir_file_count - 1], chunk->file_fd[chunk->redir_file_count - 1]);// @debug
		if (dup2(chunk->file_fd[chunk->redir_file_count - 1], STDOUT_FILENO) == -1)
			strerror(errno); // @optimize
		close(chunk->file_fd[chunk->redir_file_count - 1]); //@optimize : peut etre rendu plus robust avec strerror et errno
		chunk->file_open[chunk->redir_file_count - 1] = false;
	}
}

void	run_cmd(t_data *data, t_exe *exe, t_chunk *chunk, int i)
{
	close_unecessary_pipes(exe, i - 1);
	redirect_input_file(data, chunk);
	redirect_to_output_file(data, chunk);
	if (i > 0 && !chunk->has_input_redir && dup2(exe->pipe_arr[i - 1][0], STDIN_FILENO) == -1)
		strerror(errno); // @optimize
	if (i >= 0 && i < exe->total_cmd_count - 1)
		close(exe->pipe_arr[i][0]);
	if (i < exe->total_cmd_count - 1 && !chunk->has_redir && dup2(exe->pipe_arr[i][1], STDOUT_FILENO) == -1)
		strerror(errno); // @optimize
	if (i < exe->total_cmd_count - 1)
		close(exe->pipe_arr[i][1]);
	execve(chunk->argv[0], chunk->argv, data->env);
	exit(127);
		//clean_cmds_exit(data, EXIT_FAILURE/* , "Error executing first cmd\n" */);
		//exit(EXIT_FAILURE);// quitte juste le sous process
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

void	init_pid_arr(t_data *data, t_exe *exe)
{
	int i;

	if (!data)
		return;
	i = 0;
	exe->pid_arr = malloc(exe->valid_cmd_count * sizeof(int));
	if (!exe->pid_arr)
		strerror(errno);
		//clean_cmds_exit(data, EXIT_FAILURE/* , "Malloc err pid_arr" */); //@optimize, normalement dans pipex, cela supprimer faisait un exit, donc la suite du program n'etait pas execute. Ici ce n'est plus le cas, il faut donc gerer differament pour etre sur de ne pas avoir des free multiples etc;
	exe->pid_arr_malloced = true;
	while (i < exe->valid_cmd_count)
		exe->pid_arr[i++] = -2;
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
		if (i_node && (t_chunk *)i_node->content && ((t_chunk *)i_node->content)->type != CMD)
		{
			i_node = i_node->next;
			continue ;
		}
		if (data->exec_info.cmd_is_valid_arr[i] == true)
		{
			data->exec_info.pid_arr[i] = fork();
			if (data->exec_info.pid_arr[i] == -1)
				strerror(errno);
				//clean_cmds_exit(data, EXIT_FAILURE/* , "Error in forking: run_pipex" */);
			if (data->exec_info.pid_arr[i] == 0)
				run_cmd (data, &data->exec_info, ((t_chunk *)i_node->content), i);
		}
		i++;
		i_node = i_node->next;
	}
	close_all_pipes(&data->exec_info, &data->exec_info.pipe_arr);
	waiting_childs(&data->exec_info, data->exec_info.pid_arr);
}


int main_exec(t_data *data)
{
	if (data)
	{
		init_files(data); // OK for now
		init_input_files(data);
		init_cmd(data);
		run_pipex(data);
	}
	return(EXIT_SUCCESS);
}
