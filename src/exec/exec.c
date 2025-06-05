/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 10:30:25 by ofilloux          #+#    #+#             */
/*   Updated: 2025/06/05 10:56:01 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	run_pipex(t_data *data, t_exe *exe, t_chunk *chunk, int i)
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
	if (0 != execve_builtin_in_child(data, exe, chunk, i))
		execve(chunk->argv[0], chunk->argv, data->env);
	if (exe->total_cmd_count > 1)
	{
		free_resources(data, true, true);
		exit(127);
	}
}

static void	waiting_childs(t_data *data, t_exe *exe, int *pid_arr)
{
	int	i;

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
	int	i;

	if (!data)
		return ;
	i = 0;
	exe->pid_arr = malloc(exe->valid_cmd_count * sizeof(int));
	if (!exe->pid_arr)
		strerror(errno);
	exe->pid_arr_malloced = true;
	while (i < exe->valid_cmd_count)
		exe->pid_arr[i++] = -2;
}

int	main_exec(t_data *data)
{
	if (data)
	{
		init_files(data);
		init_input_files(data);
		init_cmd(data);
		init_pid_arr(data, &data->exe_nfo);
		init_pipes_2arr(data, &data->exe_nfo);
		exec_cmds(data, 0);
		close_all_pipes(&data->exe_nfo, &data->exe_nfo.pipe_arr);
		waiting_childs(data, &data->exe_nfo, data->exe_nfo.pid_arr);
		clean_exe_nfo(data, data->exit_status);
		if (data->exe_nfo.cmd_err_msg != NULL && \
			data->exe_nfo.command_err_count == data->exe_nfo.total_cmd_count)
			printf("%s\n", data->exe_nfo.cmd_err_msg);
	}
	return (EXIT_SUCCESS);
}
