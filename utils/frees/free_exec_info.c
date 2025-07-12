/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exe_nfo.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 19:00:27 by ofilloux          #+#    #+#             */
/*   Updated: 2025/06/04 13:07:54 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	cmd_error_msg(t_data *data)
{
	char	*msg;

	msg = data->exe_nfo.cmd_err_msg;
	if (msg)
		write(STDERR_FILENO, msg, ft_strlen(msg));
	if (data->cmd_list && data->exe_nfo.has_msg && msg)
		ft_free((void **) &data->exe_nfo.cmd_err_msg);
}

void	clean_exe_nfo(t_data *data)
{
	if (data && data->cmd_list)
	{
		if (data->exe_nfo.cmd_is_valid_arr)
			ft_free((void **) &data->exe_nfo.cmd_is_valid_arr);
		if (data->exe_nfo.pid_arr_malloced == true)
			ft_free((void **) &data->exe_nfo.pid_arr);
		if (data->exe_nfo.pipe_arr_malloced == true)
			free_pipes_arr(data->exe_nfo.pipe_arr, &data->exe_nfo);
		if (data->exe_nfo.pipes_malloced)
			ft_free((void **) &data->exe_nfo.pipes_malloced);
	}
}
