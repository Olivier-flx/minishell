/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 16:40:29 by marvin            #+#    #+#             */
/*   Updated: 2025/05/10 16:40:29 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void reset_data(t_data *data)
{
    if (data->cmd_list)
        free_cmdlist(data->cmd_list);
    data->cmd_list = NULL;
    g_signal_received = 0;
}
