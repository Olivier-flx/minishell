/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 16:00:49 by ofilloux          #+#    #+#             */
/*   Updated: 2025/05/14 14:56:19 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

bool	line_only_contain_pipes(char *line)
{
	int i = 0;
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
		return;
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

void	listen_incomplete_lines(t_data *data, char **line)
{
	while (*line && line_is_incomplete(*line))
	{
		signal_handlers_for_readline(data);
		if (!tocken_quote_closed(*line))
			*line = c_strjoin(*line, readline("\033[1mdquote> \033[0m"), '\n');
		else if (!line_accolade_closed(*line))
			*line = c_strjoin(*line, readline("> "), '\n');
		else if (line_finish_by_pipe(*line))
			*line = c_strjoin(*line, readline("> "), '\n');
		else if (line_finish_by_backslash(*line))
		{
			remove_trailing_backslash(*line);
			*line = strjoin_and_free(*line, readline("> "));
		}
	}
}
