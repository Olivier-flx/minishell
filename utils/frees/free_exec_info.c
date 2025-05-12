/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exec_info.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 19:00:27 by ofilloux          #+#    #+#             */
/*   Updated: 2025/05/12 20:43:12 by ofilloux         ###   ########.fr       */
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
	//printf("msg _ %s\n", msg);
	if (data->cmd_list && data->exec_info.has_msg && msg)
		ft_free((void **) &data->exec_info.cmd_err_msg);
}

void	clean_exec_info(t_data *data, int exit_val)
{
	(void) exit_val;

	if (data && data->cmd_list)
	{
		if (data->exec_info.env_path && data->exec_info.env_path[0])
			ft_free((void **) &data->exec_info.env_path);
		if (data->exec_info.cmd_is_valid_arr)
			ft_free((void **) &data->exec_info.cmd_is_valid_arr);
		if (data->exec_info.pid_arr_malloced == true)
			ft_free((void **) &data->exec_info.pid_arr);
		if (data->exec_info.pipe_arr_malloced == true)
			free_pipes_arr(data->exec_info.pipe_arr, &data->exec_info);
		if (data->exec_info.pipes_malloced)
			ft_free((void **) &data->exec_info.pipes_malloced);
		//free_cmdlist(data->cmd_list);
	}
	cmd_error_msg(data, exit_val);
}
