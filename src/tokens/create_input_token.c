/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_input_token.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 17:57:45 by ofilloux          #+#    #+#             */
/*   Updated: 2025/07/12 10:35:24 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	initialize_input_redir(t_chunk **tok)
{
	(*tok)->has_input_redir = false;
	(*tok)->input_redir_count = 0;
	(*tok)->input_redir = NULL;
	(*tok)->input_redir_file_count = 0;
	(*tok)->input_redir_file = NULL;
	(*tok)->input_file_fd = NULL;
	(*tok)->input_file_fd_malloced = NULL;
	(*tok)->input_file_open = NULL;
	(*tok)->input_file_open_malloced = NULL;
	(*tok)->has_here_doc = false;
}

void	inititalize_redir(t_chunk **tok)
{
	(*tok)->has_redir = false;
	(*tok)->redir_count = 0;
	(*tok)->redir_file_count = 0;
	(*tok)->redir = NULL;
	(*tok)->redir_files = NULL;
	(*tok)->file_fd = NULL;
	(*tok)->file_fd_malloced = NULL;
	(*tok)->file_open = NULL;
	(*tok)->file_open_malloced = NULL;
}

t_chunk	*initialize_t_chunk1(void)
{
	t_chunk	*tok;

	tok = NULL;
	tok = malloc(sizeof(t_chunk));
	if (!tok)
		return (NULL);
	tok->tokens = NULL;
	tok->argv = NULL;
	tok->av_0_nopath = NULL;
	tok->bin_path = NULL;
	tok->type = CMD;
	tok->nb_heredocs = 0;
	tok->heredoc_pipe_arr_malloced = false;
	tok->heredoc_pipe_arr = NULL;
	tok->pipes_malloced = NULL;
	inititalize_redir(&tok);
	initialize_input_redir(&tok);
	tok->len = 0;
	tok->quotes = (t_quote){0};
	return (tok);
}

t_chunk	*create_token(char ***str, t_chk_type type, int i, t_quote quotes)
{
	t_chunk	*token;

	token = initialize_t_chunk1();
	token->tokens = *str;
	token->type = type;
	token->index = i;
	token->quotes = quotes;
	return (token);
}
