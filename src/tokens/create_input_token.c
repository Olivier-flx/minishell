/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_input_token.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 17:57:45 by ofilloux          #+#    #+#             */
/*   Updated: 2025/04/11 18:49:55 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"


t_chunk	*initialize_t_chunk1(void)
{

	t_chunk	*tok;

	tok = malloc(sizeof(t_chunk));
	if (!tok)
		return (NULL);
	tok->tokens = NULL;
	tok->argv = NULL;
	tok->type = CMD;
	tok->has_redir = false;
	tok->redir_count = 0;
	tok->redir_file_count = 0;
	tok->redir = NULL;// list of redir in a chunk ex: > >> >
	tok->redir_files = NULL;// ex:test ; test1; test2
	tok->input_redir = NULL;
	tok->input_redir_file = NULL;
	tok->index = 0; // util ?
	tok->len = 0; // util ?
	tok->quotes = (t_quote) {0}; // util ?
	return (tok);
}


t_chunk	*create_token(char ***str, int type, int i, t_quote quotes)
{
	t_chunk	*token;

	token = initialize_t_chunk1();
	if (!token)
		return (NULL);
	token->tokens = *str;
	token->type = type;
	token->index = i;
	if (type == OPERATOR)
		token->len = s_len(*str[0]);
	else
		token->len = 0; //TODO
	token->quotes = quotes;
	return (token);
}
