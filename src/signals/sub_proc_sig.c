/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub_proc_sig.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 22:17:16 by ofilloux          #+#    #+#             */
/*   Updated: 2025/06/09 10:57:32 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	handle_sub_process_signal(t_data *data, int status, bool *printed)
{
	int		sig;

	if (!status)
		return ;
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
			data->exit_status = 128 + SIGQUIT;
		}
		else if (sig == SIGINT)
			data->exit_status = 128 + SIGINT;
		else
			data->exit_status = 128 + sig;
	}
	else
		data->exit_status = (status >> 8) & 0xFF;
}
