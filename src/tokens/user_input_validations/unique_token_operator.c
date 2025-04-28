/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unique_token_operator.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 11:28:48 by ofilloux          #+#    #+#             */
/*   Updated: 2025/04/28 19:55:28 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"


//check cases where there is only an operator in a chunk
// for instance `>` or `hello | > | world`
static char	*unexpected_token(t_dlist *i_node)
{
	if (!i_node->next)
		return ("newline");
	if(((t_chunk *)(i_node->next->content))->tokens[0])
		return(((t_chunk *)(i_node->next->content))->tokens[0]);
	return ("undefined");
}

int	check_for_simple(t_dlist **cmd_list)
{
	t_dlist	*i_node;
	t_quote	quotes;
	t_chunk	*chunk;

	init_quotes(&quotes);
	i_node = *cmd_list;
	while (i_node && (t_chunk *)i_node->content)
	{
		chunk = (t_chunk *)i_node->content;
		if(chunk->tokens && chunk->tokens[0])
		{
			if (is_operator(chunk->tokens[0], 0, &quotes) && !chunk->tokens[1])
				return (printf("bash: syntax error near unexpected token `%s'\n",\
					unexpected_token(i_node)), ERROR);
		}
		i_node = i_node->next;
	}
	return (0);
}
