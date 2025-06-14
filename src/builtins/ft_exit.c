/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 17:48:14 by marvin            #+#    #+#             */
/*   Updated: 2025/06/14 15:25:27 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	exit_arg(t_data *data, char **args)
{
	int	i;

	i = 0;
	while (args[1][i])
	{
		if (!ft_isdigit(args[1][i]) && \
		!(i == 0 && (args[1][i] == '+' || args[1][i] == '-')))
		{
			write(STDERR_FILENO, \
				"minishell: exit: numeric argument required\n", 43);
			free_resources(data, true, true);
			data->exit_code = 255;
			data->exit_required = true;
		}
		i++;
	}
}

int	ft_exit(t_data *data, char **args)
{
	write(STDERR_FILENO, "exit\n", 5);
	if (args && args[1])
	{
		exit_arg(data, args);
		if (args[2])
		{
			write(STDERR_FILENO, "minishell: exit: too many arguments\n", 36);
			data->exit_status = 1;
			return (1);
		}
		free_resources(data, true, true);
		data->exit_code = (ft_atoi(args[1]) % 256);
		data ->exit_required = true;
	}
	free_resources(data, true, true);
	data->exit_code = 0;
	data ->exit_required = true;
	return (0);
}
