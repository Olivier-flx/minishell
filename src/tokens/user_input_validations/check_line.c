/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 16:00:49 by ofilloux          #+#    #+#             */
/*   Updated: 2025/05/12 16:11:53 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

bool	line_finish_by_pipe(char **line)
{
	int	i;

	if (!*line || ft_strlen(*line) == 0) {
		return false;
	}
	i = ft_strlen(*line) - 1;
	while (i >= 0 && (*line)[i] == ' ') {
		i--;
	}
	if (i >= 0 && (*line)[i] == '|') {
		*line = c_strjoin(*line, readline("> "), '\n');
		return true;
	}
	return false;
}

void	listen_incomplete_lines(char **line)
{
	int flag;

	flag = 0;
	while (*line && flag == 0 &&  (!tocken_quote_closed(*line) \
		|| !line_accolade_closed(*line) \
		|| (*line)[ft_strlen(*line) - 1] == '|' \
		|| (*line)[ft_strlen(*line) - 1] == ' '))
	{
		/// NEED TO HANDLE SIGNAL HERE AND IN EVERY SUB-WHILE
		while (*line && !tocken_quote_closed(*line))
			*line = c_strjoin(*line, readline("\033[1mdquote> \033[0m"), '\n');
		while (*line && !line_accolade_closed(*line))
			*line = c_strjoin(*line, readline("> "), '\n');
		while (*line && line_finish_by_pipe(line))
			flag = 1;
	}
}
