/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 10:30:25 by ofilloux          #+#    #+#             */
/*   Updated: 2025/07/13 21:29:40 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	handle_sub_process_signal2(t_data *data, int status, bool *printed)
{
	int		sig;

	(void) data;
	if (!status)
		return (-1);
	if ((status & 0x7F) != 0)
	{
		sig = status & 0x7F;
		if (sig == SIGQUIT)
		{
			if (!(*printed))
			{
				write(STDOUT_FILENO, "Quit (core dumped)\n", 20);
				*printed = true;
			}
			return (128 + SIGQUIT);
		}
		else if (sig == SIGINT)
			return (128 + SIGINT);
		else
			return (128 + sig);
	}
	else
	{
		return ((status >> 8) & 0xFF);
		//fprintf(stderr, "handle_sub_process_signal  cmd %i ,  data->exit_status %i",i, data->exit_status); // debug
	}
}


// static void	waiting_childs(t_data *data, t_exe *exe, int *pid_arr)
// {
// 	int		i;
// 	int		status;
// 	bool	printed;

// 	if (!data)
// 		return ;
// 	i = 0;
// 	printed = false;
// 	while (i < exe->valid_cmd_count)
// 	{
// 		if (exe->cmd_is_valid_arr[i])
// 		{
// 			status = 0;
// 			waitpid(pid_arr[i], &status, 0);
// 			handle_sub_process_signal(data, status, &printed);
// 		}
// 		i++;
// 	}
// }
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
	while (i < exe->total_cmd_count) // @ti3
	{
			status = 0;
			waitpid(pid_arr[i], &status, 0);
			exit_code = handle_sub_process_signal2(data, status, &printed);
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
	exe->pid_arr = malloc(exe->total_cmd_count * sizeof(int)); // @ti3
	if (!exe->pid_arr)
		strerror(errno);
	exe->pid_arr_malloced = true;
	while (i < exe->total_cmd_count) // @ti3
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
