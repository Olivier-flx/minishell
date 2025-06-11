/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 18:10:10 by ofilloux          #+#    #+#             */
/*   Updated: 2025/05/14 17:45:31 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

static void	handle_path_and_builtin(t_data *data, t_exe *exec_info, t_chunk *chunk)
{
	if (usr_input_got_slash(chunk->argv[0]) == 0 && !is_builtin(chunk->argv[0]))
	{
		if (exec_info->env_path_found == false)
			get_path(chunk->argv[0], exec_info, data->env_list);
		if (exec_info->env_path_found == true)
		{
			chunk->argv_0_nopath = ft_strdup(chunk->argv[0]);
			ft_free((void **) &chunk->argv[0]);
			chunk->argv[0] = ft_strjoin(exec_info->env_path, chunk->argv_0_nopath);
		}
	}
}

void	init_cmd_vect(t_data *data, t_dlist **cmd_list, t_exe *exec_info)
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
			exec_info->cmd_is_valid_arr[i] = false;
			handle_path_and_builtin(data, exec_info, chunk);
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
	exe_info->cmd_is_valid_arr_malloced = true;
	return ;
}

void	init_cmd(t_data *data)
{
	data->exec_info.total_cmd_count = count_cmd(&data->cmd_list);
	init_cmd_is_valid_arr(&data->exec_info, data->exec_info.total_cmd_count);
	data->exec_info.env_path = NULL;
	data->exec_info.env_path_found = false;
	data->exec_info.pid_arr = NULL;
	data->exec_info.pid_arr_malloced = false;
	data->exec_info.pipe_arr = false;
	data->exec_info.pipe_arr_malloced = false;
	data->exec_info.pipes_malloced = false;
	data->exec_info.cmd_err_msg = NULL;
	data->exec_info.has_msg = false;
	data->exec_info.valid_cmd_count = 0;
	data->exec_info.command_err_count = 0;
	data->exec_info.last_status_code = 0;
	init_cmd_vect(data, &data->cmd_list, &data->exec_info);
	check_wrong_commands(data);
	init_bool_pipes_malloced(data, &data->exec_info);
	return ;
}
