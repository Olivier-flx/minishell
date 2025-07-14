/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 10:30:25 by ofilloux          #+#    #+#             */
/*   Updated: 2025/07/14 12:56:13 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

static void	waiting_childs(t_data *data, t_exe *exe, int *pid_arr)
{
	int		i;
	int		status;
	bool	printed;
	int		final_exit_status;
	int		exit_code;

	if (!data)
		return ;
	final_exit_status = 0;
	exit_code = 0;
	i = 0;
	printed = false;
	while (i < exe->total_cmd_count)
	{
		status = 0;
		waitpid(pid_arr[i], &status, 0);
		exit_code = handle_sub_process_signal(status, &printed);
		if (i + 1 == exe->total_cmd_count && exit_code >= 0)
			final_exit_status = exit_code;
		i++;
	}
	if (exit_code >= 0)
		data->exit_status = final_exit_status;
}

void	init_pid_arr(t_data *data, t_exe *exe)
{
	int	i;

	if (!data)
		return ;
	i = 0;
	exe->pid_arr = malloc(exe->total_cmd_count * sizeof(int));
	if (!exe->pid_arr)
		strerror(errno);
	exe->pid_arr_malloced = true;
	while (i < exe->total_cmd_count)
		exe->pid_arr[i++] = -2;
}
// void	init_pid_arr(t_data *data, t_exe *exe)
// {
// 	int	i;

// 	if (!data)
// 		return ;
// 	i = 0;
// 	exe->pid_arr = malloc(exe->valid_cmd_count * sizeof(int));
// 	if (!exe->pid_arr)
// 		strerror(errno);
// 	exe->pid_arr_malloced = true;
// 	while (i < exe->valid_cmd_count)
// 		exe->pid_arr[i++] = -2;
// }

void	exec_cmds(t_data *data, int i)
{
	int		valid_cmd_i;
	t_dlist	*i_node;
	t_chunk	*chunk;

	i_node = data->cmd_list;
	valid_cmd_i = 0;
	while (i < data->exe_nfo.total_cmd_count)
	{
		chunk = (t_chunk *)i_node->content;
		if (((t_chunk *)i_node->content)->type == EMPTY)
			i++;
		if (((t_chunk *)i_node->content)->type == EMPTY \
			|| (i_node && chunk && chunk->type != CMD))
		{
			i_node = i_node->next;
			continue ;
		}
		process_command_iteration(data, chunk, i, &valid_cmd_i);
		i++;
		i_node = i_node->next;
	}
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
		cmd_error_msg(data);
		waiting_childs(data, &data->exe_nfo, data->exe_nfo.pid_arr);
		clean_exe_nfo(data);
	}
	return (EXIT_SUCCESS);
}
