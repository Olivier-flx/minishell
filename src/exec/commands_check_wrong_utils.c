/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_check_wrong_utils.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 11:23:09 by ofilloux          #+#    #+#             */
/*   Updated: 2025/07/12 11:26:19 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	set_exec_last_status_code(t_data *data, int i)
{
	data->exe_nfo.command_err_count++;
	data->exe_nfo.cmd_is_valid_arr[i] = false;
	if (i == data->exe_nfo.total_cmd_count - 1)
		data->exe_nfo.last_status_code = 127;
	else
		data->exe_nfo.last_status_code = 0;
}
