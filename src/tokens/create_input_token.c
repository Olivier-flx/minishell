/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_input_token.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 17:57:45 by ofilloux          #+#    #+#             */
/*   Updated: 2025/04/07 17:12:17 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

t_chunk	*create_token(char ***str, int type, int i, t_quote quotes)
{
	t_chunk	*token;

	token = malloc(sizeof(t_chunk));
	if (!token)
		return (NULL);
	token->content = *str;
	token->type = type;
	token->index = i;
	if (type == OPERATOR)
		token->len = s_len(*str[0]);
	else
		token->len = 0; //TODO
	token->quotes = quotes;
	return (token);
}
