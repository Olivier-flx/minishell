/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listen_heredocs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 17:41:15 by ofilloux          #+#    #+#             */
/*   Updated: 2025/06/09 10:31:01 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	listen_terminal2(t_chunk *chunk, char *limiter, int i_to_herdoc_index)
{
	char	*line;
	int		limiter_len;

	line = NULL;
	limiter_len = (int) ft_strlen(limiter);
	while (1)
	{
		line = readline("> ");
		if (!line && write(STDERR_FILENO, "Error reading from terminal\n", 29))
			break ;
		if (ft_strncmp(line, limiter, limiter_len) == 0 \
				&& (int) ft_strlen(line) == limiter_len)
			break ;
		write (chunk->heredoc_pipe_arr[i_to_herdoc_index][1], \
			line, ft_strlen(line));
		write(chunk->heredoc_pipe_arr[i_to_herdoc_index][1], "\n", 1);
		ft_free ((void **) &line);
	}
	ft_free ((void **) &line);
	return (0);
}

int	listen_heredocs(t_data *data, t_chunk *chunk)
{
	int	i_to_herdoc_index;
	int	i;

	if (!data || !chunk->has_here_doc || !chunk->input_redir)
		return (EXIT_FAILURE);
	init_pipes_2arr_for_heredoc(data, chunk);
	i = 0;
	i_to_herdoc_index = 0;
	while (chunk->input_redir[i])
	{
		if (ft_strcmp("<<", chunk->input_redir[i]) == 0)
		{
			listen_terminal2(chunk, chunk->input_redir_file[i], \
				i_to_herdoc_index);
			close(chunk->heredoc_pipe_arr[i_to_herdoc_index][1]);
			i_to_herdoc_index++;
		}
		i++;
	}
	return (0);
}
