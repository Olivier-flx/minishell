/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cmd_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 19:00:27 by ofilloux          #+#    #+#             */
/*   Updated: 2025/05/08 10:51:59 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	cmd_error_msg(t_data *data, int failure)
{
	char *msg;

	msg = data->exec_info.cmd_err_msg;
	data->exec_info.last_status_code = failure;
	if (msg)
		write(STDERR_FILENO, msg, ft_strlen(msg));
	if (data->cmd_list && msg)
		free(msg);
}

void	clean_cmds_exit(t_data *data, int exit_val, char *msg)
{
	int	i;
	t_dlist	*i_node;

	i = 0;
	i_node = data->cmd_list;
	if (data && data->cmd_list)
	{
		if (data->exec_info.env_path && data->exec_info.env_path[0])
			free(data->exec_info.env_path);
		if (data->exec_info.cmd_is_valid_arr);
			free(data->exec_info.cmd_is_valid_arr);
		if (data->exec_info.pid_arr_malloced == true)
			free(data->exec_info.pid_arr);
		if (data->exec_info.pipe_arr_malloced == true)
			free_pipes_arr(data->exec_info.pipe_arr, &data->exec_info);
		if (data->exec_info.pipes_malloced)
			free(data->exec_info.pipes_malloced);
		free_cmdlist(data->cmd_list);
	}
	cmd_error_msg(data, exit_val);
}
