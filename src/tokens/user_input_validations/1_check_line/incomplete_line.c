/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   incomplete_line.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 13:27:40 by ofilloux          #+#    #+#             */
/*   Updated: 2025/06/23 16:25:15 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../header/minishell.h"

void	listen_incomplete_lines(t_data *data, char **line)
{
	while (*line && line_is_incomplete(*line))
	{
		signal_handlers_for_readline(data);
		if (!tocken_quote_closed(*line))
			*line = strjoin_and_free(*line, readline("\033[1mdquote> \033[0m"));
		else if (!line_accolade_closed(*line))
			*line = strjoin_and_free(*line, readline("> "));
		else if (line_finish_by_pipe(*line))
			*line = strjoin_and_free(*line, readline("> "));
		else if (line_finish_by_backslash(*line))
		{
			remove_trailing_backslash(*line);
			*line = strjoin_and_free(*line, readline("> "));
		}
	}
}
