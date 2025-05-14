/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preliminary_checks.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 10:37:33 by ofilloux          #+#    #+#             */
/*   Updated: 2025/05/14 11:00:24 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

bool	line_is_colon(t_data *data, char *line)
{
	if (line && 1 == ft_strlen(line) && line[0] == ':')
	{
		data->exit_status = 0;
		return (true);
	}
	return (false);
}

bool	line_is_exlamation_point(t_data *data, char *line)
{
	if (line && 1 == ft_strlen(line) && line[0] == '!')
	{
		data->exit_status = 1;
		return (true);
	}
	return (false);
}

bool	preliminary_checks_ok(t_data *data, char* line)
{
	if (!line)
		return (false);
	if (line_is_colon(data, line))
		return (false);
	if (line_is_exlamation_point(data, line))
		return (false);
	if (line_is_only_spaces(line))
	{
		data->exit_status = 0;
		return (false);
	}
	return (true);
}
