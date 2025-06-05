/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 17:55:52 by ofilloux          #+#    #+#             */
/*   Updated: 2025/06/05 10:52:01 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

static void	process_command_iteration(t_data *data, t_chunk *chunk, int i, \
									int *valid_cmd_i)
{
	listen_heredocs(data, chunk);
	if (data->exe_nfo.cmd_is_valid_arr[i] == true)
	{
		if (run_builtins(data, &data->exe_nfo, chunk, i) != 1)
		{
			data->exe_nfo.pid_arr[*valid_cmd_i] = fork();
			if (data->exe_nfo.pid_arr[*valid_cmd_i] == -1)
				strerror(errno);
			if (data->exe_nfo.pid_arr[*valid_cmd_i] == 0)
				run_pipex(data, &data->exe_nfo, chunk, i);
		}
		(*valid_cmd_i)++;
	}
	close_heredocs_pipes(chunk);
}

void	exec_cmds(t_data *data, int i)
{
	int		valid_cmd_i;
	t_dlist	*i_node;

	i_node = data->cmd_list;
	valid_cmd_i = 0;
	while (i < data->exe_nfo.total_cmd_count)
	{
		t_chunk *chunk = (t_chunk *)i_node->content;
		if (i_node && chunk && chunk->type != CMD)
		{
			i_node = i_node->next;
			continue ;
		}
		process_command_iteration(data, chunk, i, &valid_cmd_i);
		i++;
		i_node = i_node->next;
	}
}

/* void	exec_cmds(t_data *data, int i)
{
	int		valid_cmd_i;
	t_dlist	*i_node;

	i_node = data->cmd_list;
	valid_cmd_i = 0;
	while (i <  data->exe_nfo.total_cmd_count)
	{
		if (i_node && (t_chunk *)i_node->content && ((t_chunk *)i_node->content)->type != CMD)
		{
			i_node = i_node->next;
			continue ;
		}
		listen_heredocs(data, (t_chunk *)i_node->content);
		if (data->exe_nfo.cmd_is_valid_arr[i] == true)
		{
			if (1 != run_builtins(data, &data->exe_nfo, ((t_chunk *)i_node->content), i))
			{
				data->exe_nfo.pid_arr[valid_cmd_i] = fork();
				if (data->exe_nfo.pid_arr[valid_cmd_i] == -1)
					strerror(errno);
				if (data->exe_nfo.pid_arr[valid_cmd_i] == 0)
					run_pipex (data, &data->exe_nfo, ((t_chunk *)i_node->content), i);
			}
			valid_cmd_i++;
		}
		close_heredocs_pipes((t_chunk *)i_node->content);
		i++;
		i_node = i_node->next;
	}
} */
