/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 10:30:25 by ofilloux          #+#    #+#             */
/*   Updated: 2025/06/09 21:29:19 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

static void	waiting_childs(t_data *data, t_exe *exe, int *pid_arr)
{
	int		i;
	int		status;
	bool	printed;

	if (!data)
		return ;
	i = 0;
	printed = false;
	while (i < exe->valid_cmd_count)
	{
		if (exe->cmd_is_valid_arr[i])
		{
			status = 0;
			waitpid(pid_arr[i], &status, 0);
			handle_sub_process_signal(data, status, &printed);
		}
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
		waiting_childs(data, &data->exe_nfo, data->exe_nfo.pid_arr);
		clean_exe_nfo(data, data->exit_status);
		if (data->exe_nfo.cmd_err_msg != NULL && \
			data->exe_nfo.command_err_count == data->exe_nfo.total_cmd_count)
			printf("%s\n", data->exe_nfo.cmd_err_msg);
	}
	return (EXIT_SUCCESS);
}
