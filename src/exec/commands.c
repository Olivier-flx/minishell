/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 18:10:10 by ofilloux          #+#    #+#             */
/*   Updated: 2025/07/12 17:37:54 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

/**
 * @brief Checks and prepares the path for a non-builtin command.
 *
 * If the command does not contain a slash and is not a builtin,
 * this function attempts to resolve its path using the environment variables.
 * If the path is found, it updates the chunk's argv[0] with the full path,
 * constructed from the environment path and the original command name.
 *
 * @param data		Structure containing global shell data.
 * @param exe_nfo	Structure containing execution-related information.
 * @param chnk		Chunk containing the command and its arguments.
 */
static void	handle_path_and_builtin(t_data *data, t_chunk *chnk)
{
	chnk->bin_path = NULL;
	if (usr_input_got_slash(chnk->argv[0]) == 0 && !is_builtin(chnk->argv[0]))
	{
		get_path(chnk->argv[0], chnk, data->env_list);
		if (chnk->bin_path != NULL)
		{
			chnk->av_0_nopath = ft_strdup(chnk->argv[0]);
			chnk->exec = ft_strjoin(chnk->bin_path, chnk->av_0_nopath);
		}
		else
			chnk->exec = ft_strdup(chnk->argv[0]);
	}
	else if (usr_input_got_slash(chnk->argv[0]))
		chnk->exec = ft_strdup(chnk->argv[0]);
}

/**
 * @brief Initializes the command vector from a linked list of command chunks.
 *
 * Iterates through each node in the command list. For each valid command chunk,
 * it sets its execution validity to false and calls handle_path_and_builtin
 * to manage path resolution and builtin checking.
 *
 * @param data		Structure containing global shell data.
 * @param cmd_list	Doubly linked list containing command chunks.
 * @param exe_nfo	Structure containing execution-related information.
 */
void	init_cmd_vect(t_data *data, t_dlist **cmd_list, t_exe *exe_nfo)
{
	t_dlist	*i_node;
	t_chunk	*chunk;
	int		i;

	i_node = *cmd_list;
	i = 0;
	while (i_node)
	{
		chunk = (t_chunk *) i_node->content;
		if (chunk->type == CMD && chunk->argv && chunk->argv[0])
		{
			exe_nfo->cmd_is_valid_arr[i] = false;
			handle_path_and_builtin(data, chunk);
			i++;
		}
		i_node = i_node->next;
	}
}
/* dans piper 	char	***cmd_vect;
cmd_vect = cmd_list et cmd_vect[0] = cmd_list->content->argv */

void	init_cmd_is_valid_arr(t_exe *exe_info, int nb_cmd)
{
	exe_info->cmd_is_valid_arr = NULL;
	exe_info->cmd_is_valid_arr_malloced = false;
	exe_info->cmd_is_valid_arr = malloc(sizeof(bool) * (nb_cmd + 1));
	if (!exe_info->cmd_is_valid_arr)
		return ;
	ft_memset(exe_info->cmd_is_valid_arr, 0, sizeof(bool) * (nb_cmd + 1));
	exe_info->cmd_is_valid_arr_malloced = true;
	return ;
}

void	init_cmd(t_data *data)
{
	data->exe_nfo.total_cmd_count = count_cmd(&data->cmd_list);
	init_cmd_is_valid_arr(&data->exe_nfo, data->exe_nfo.total_cmd_count);
	data->exe_nfo.pid_arr = NULL;
	data->exe_nfo.pid_arr_malloced = false;
	data->exe_nfo.pipe_arr = false;
	data->exe_nfo.pipe_arr_malloced = false;
	data->exe_nfo.pipes_malloced = false;
	data->exe_nfo.cmd_err_msg = NULL;
	data->exe_nfo.has_msg = false;
	data->exe_nfo.valid_cmd_count = 0;
	data->exe_nfo.command_err_count = 0;
	data->exe_nfo.last_status_code = 0;
	init_cmd_vect(data, &data->cmd_list, &data->exe_nfo);
	check_wrong_commands(data);
	init_bool_pipes_malloced(data, &data->exe_nfo);
	return ;
}
