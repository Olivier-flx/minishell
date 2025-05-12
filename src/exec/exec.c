/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 10:30:25 by ofilloux          #+#    #+#             */
/*   Updated: 2025/05/12 17:07:25 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

/* void redirect_input_file(t_data *data, t_chunk *chunk)
{
	int	i;
	int	lst_redir;

	i = 0;
	lst_redir = chunk->input_redir_count + chunk->nb_heredocs - 1;
	if (!data)
		return;
	while (chunk->input_redir && chunk->input_redir[i])
	{
		//listen_heredocs(chunk, i);
		if(ft_strcmp(chunk->input_redir[i], "<") == 0)
		{
			chunk->input_file_fd[i] = open(chunk->input_redir_file[i], O_RDONLY);
			if (chunk->input_file_fd[0] < 0)
				strerror(errno); // @optimize
			chunk->input_file_open[0] = true;
			if (i == lst_redir && dup2(chunk->input_file_fd[i], STDIN_FILENO) == -1)
				strerror(errno); // @optimize
			close(chunk->input_file_fd[i]);
			chunk->input_file_open[i] = false;
		}
		i++;
	}
	if (chunk->heredoc_pipe_arr_malloced)
		ft_free((void ** ) &chunk->heredoc_pipe_arr);
	// if (dup2(files[0].fd, STDIN_FILENO) == -1)
	// 	clean_exec_info(cmd, EXIT_FAILURE, "Err dup2 : input file\n");
	// close(files[0].fd);
	//files[0].file_open = false;
} */

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
	if (0 != run_builtins(data, exe, chunk, i))
		execve(chunk->argv[0], chunk->argv, data->env);
	if (exe->total_cmd_count > 1)
		exit(127);
}

static void	waiting_childs(t_data *data, t_exe *exe, int *pid_arr)
{
	int i;

	i = 0;
	while (i < exe->valid_cmd_count)
	 {
		if (exe->total_cmd_count == 1 \
				&& exe->cmd_is_valid_arr[i] \
				&& !is_builtin(((t_chunk *)data->cmd_list->content)->argv[0]))
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
		//clean_exec_info(data, EXIT_FAILURE/* , "Malloc err pid_arr" */); //@optimize, normalement dans pipex, cela supprimer faisait un exit, donc la suite du program n'etait pas execute. Ici ce n'est plus le cas, il faut donc gerer differament pour etre sur de ne pas avoir des free multiples etc;
	exe->pid_arr_malloced = true;
	while (i < exe->valid_cmd_count)
		exe->pid_arr[i++] = -2;
}

void	run_pipex(t_data *data, int i)
{
	int		valid_cmd_i;
	t_dlist	*i_node;

	i_node = data->cmd_list;
	valid_cmd_i = 0;
	while (i <  data->exec_info.total_cmd_count)
	{
		if (i_node && (t_chunk *)i_node->content && ((t_chunk *)i_node->content)->type != CMD)
		{
			i_node = i_node->next;
			continue ;
		}
		listen_heredocs(data, (t_chunk *)i_node->content);
		if (data->exec_info.cmd_is_valid_arr[i] == true)
		{
			if (1 != run_builtins(data, &data->exec_info, ((t_chunk *)i_node->content), i))
			{
				data->exec_info.pid_arr[valid_cmd_i] = fork();
				if (data->exec_info.pid_arr[valid_cmd_i] == -1)
					strerror(errno);
				if (data->exec_info.pid_arr[valid_cmd_i] == 0)
					run_cmd (data, &data->exec_info, ((t_chunk *)i_node->content), i);
			}
			valid_cmd_i++;
		}
		close_heredocs_pipes((t_chunk *)i_node->content);
		i++;
		i_node = i_node->next;
	}
	close_all_pipes(&data->exec_info, &data->exec_info.pipe_arr);
	waiting_childs(data, &data->exec_info, data->exec_info.pid_arr);
}

// void	run_pipex(t_data *data)
// {
// 	int		i;
// 	int		valid_cmd_i;
// 	t_dlist	*i_node;

// 	i = 0;
// 	i_node = data->cmd_list;
// 	valid_cmd_i = 0;
// 	while (i <  data->exec_info.total_cmd_count)
// 	{
// 		if (i_node && (t_chunk *)i_node->content && ((t_chunk *)i_node->content)->type != CMD)
// 		{
// 			i_node = i_node->next;
// 			continue ;
// 		}
// 		init_pipes_2arr_for_heredoc(data, (t_chunk *)i_node->content);
// 		listen_heredocs((t_chunk *)i_node->content);
// 		if (data->exec_info.cmd_is_valid_arr[i] == true)
// 		{
// 			data->exec_info.pid_arr[valid_cmd_i] = fork();
// 			if (data->exec_info.pid_arr[valid_cmd_i] == -1)
// 				strerror(errno);
// 			if (data->exec_info.pid_arr[valid_cmd_i] == 0)
// 				run_cmd (data, &data->exec_info, ((t_chunk *)i_node->content), i);
// 			valid_cmd_i++;
// 		}
// 		close_heredocs_pipes((t_chunk *)i_node->content);
// 		i++;
// 		i_node = i_node->next;
// 	}
// 	close_all_pipes(&data->exec_info, &data->exec_info.pipe_arr);
// 	waiting_childs(&data->exec_info, data->exec_info.pid_arr);
// }


int main_exec(t_data *data)
{
	if (data)
	{
		init_files(data);
		init_input_files(data);
		init_cmd(data);
		init_pid_arr(data, &data->exec_info);
		init_pipes_2arr(data , &data->exec_info);
		run_pipex(data, 0);
		if (data->exec_info.cmd_err_msg != NULL && \
				data->exec_info.command_err_count == data->exec_info.total_cmd_count)
			printf("%s\n", data->exec_info.cmd_err_msg);
	}
	return(EXIT_SUCCESS);
}
