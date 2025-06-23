/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   incomplete_line_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 16:00:49 by ofilloux          #+#    #+#             */
/*   Updated: 2025/06/23 16:25:23 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../header/minishell.h"

bool	line_only_contain_pipes(char *line)
{
	int	i;

	i = 0;
	if (!line)
		return (false);
	while (line[i])
	{
		if (line[i] != '|' && !ft_isspace((unsigned char)line[i]))
			return (false);
		i++;
	}
	return (true);
}

bool	line_finish_by_pipe(char *line)
{
	int	i;

	if (!line || line_is_only_spaces(line) || line_only_contain_pipes(line))
		return (false);
	i = ft_strlen(line) - 1;
	while (i >= 0 && ft_isspace(line[i]))
		i--;
	return (i >= 0 && line[i] == '|');
}

bool	line_finish_by_backslash(char *line)
{
	int	i;
	int	backslash_count;

	if (!line || line_is_only_spaces(line))
		return (false);
	backslash_count = 0;
	i = ft_strlen(line) - 1;
	while (i >= 0 && line[i] == '\\')
	{
		backslash_count++;
		i--;
	}
	return (backslash_count % 2 == 1);
}

void	remove_trailing_backslash(char *line)
{
	int	len;

	if (!line)
		return ;
	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\\')
		line[len - 1] = '\0';
}

bool	line_is_incomplete(char *line)
{
	if (!line || line_is_only_spaces(line))
		return (false);
	return (
		!tocken_quote_closed(line)
		|| !line_accolade_closed(line)
		|| line_finish_by_pipe(line)
		|| line_finish_by_backslash(line)
	);
}
