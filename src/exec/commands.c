/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 18:10:10 by ofilloux          #+#    #+#             */
/*   Updated: 2025/06/06 20:01:07 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

static void	handle_path_and_builtin(t_data *data, \
									t_exe *exe_nfo, t_chunk *chnk)
{
	if (usr_input_got_slash(chnk->argv[0]) == 0 && !is_builtin(chnk->argv[0]))
	{
		if (exe_nfo->env_path_found == false)
			get_path(chnk->argv[0], exe_nfo, data->env_list);
		if (exe_nfo->env_path_found == true)
		{
			chnk->argv_0_nopath = ft_strdup(chnk->argv[0]);
			ft_free((void **) &chnk->argv[0]);
			chnk->argv[0] = ft_strjoin(exe_nfo->env_path, chnk->argv_0_nopath);
		}
	}
}

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
			handle_path_and_builtin(data, exe_nfo, chunk);
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
	data->exe_nfo.env_path = NULL;
	data->exe_nfo.env_path_found = false;
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
