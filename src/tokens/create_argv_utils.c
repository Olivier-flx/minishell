/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_argv_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 17:17:00 by ofilloux          #+#    #+#             */
/*   Updated: 2025/05/19 18:09:39 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	set_i_redir_and_bool(int *i_redir, bool *has_redir)
{
	*i_redir += 1;
	*has_redir = true;
}

int	handle_redir(t_chunk *chunk, int *i, int *i_redir)
{
	t_quote	quote;

	init_quotes(&quote);
	if (is_redirection(chunk->tokens[*i], 0, &quote) > 0) // @info: fil the t_chunk redir file with the corresponding redirections
	{
		chunk->redir[*i_redir] = ft_strdup(chunk->tokens[*i]);
		if (chunk->tokens[(*i) + 1] && chunk->redir_files)
			chunk->redir_files[*i_redir] = ft_strdup(chunk->tokens[++(*i)]);
		else
			printf("Error: No file name after a redir\n"); // @debug : error que gestionar despues en user validation function
		set_i_redir_and_bool(i_redir, &chunk->has_redir);
		return (1);
	}
	return (0);
}

int	handle_input_redir(t_chunk *chunk, int *i, int *i_in_redir)
{
	t_quote	quote;

	init_quotes(&quote);
	if (is_input_redir(chunk->tokens[*i], 0, &quote) > 0)
	{
		chunk->input_redir[*i_in_redir] = ft_strdup(chunk->tokens[*i]);
		if (chunk->tokens[(*i) + 1] && chunk->input_redir_file)
			chunk->input_redir_file[*i_in_redir] = ft_strdup(chunk->tokens[++(*i)]);
		else
			printf("Error: No file name after a input redir or no EOL\n"); // @debug : error que gestionar despues en user validation function
		set_i_redir_and_bool(i_in_redir, &chunk->has_input_redir);
		return (1);
	}
	return (0);
}
