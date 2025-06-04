/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unique_token_operator.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 11:28:48 by ofilloux          #+#    #+#             */
/*   Updated: 2025/06/04 13:24:52 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"


//check cases where there is only an operator in a chunk
// for instance `>` or `hello | > | world`
static char	*unexpected_token(t_dlist *i_node)
{
	if (!i_node->next)
		return ("newline");
	if (((t_chunk *)(i_node->next->content))->tokens[0])
		return (((t_chunk *)(i_node->next->content))->tokens[0]);
	return (NULL);
}

int	check_for_simple(t_dlist *list)
{
	t_quote	quotes;
	t_chunk	*chunk;
	int		i;

	init_quotes(&quotes);
	while (list && (t_chunk *)list->content)
	{
		chunk = (t_chunk *)list->content;
		i = -1;
		while (chunk->tokens && chunk->tokens[++i])
		{
			if (is_operator(chunk->tokens[i], 0, &quotes))
			{
				if (pp_char_len(chunk->tokens) == 1)
					return (printf("bash: syntax error near \
						unexpected token `%s'\n", \
						unexpected_token(list)), EXIT_FAILURE);
				if (pp_char_len(chunk->tokens) > 1 && i > 0 \
					&& is_operator(chunk->tokens[i - 1], 0, &quotes))
					return (printf("bash: syntax error near \
						unexpected token `%s'\n", \
						chunk->tokens[i - 1]), EXIT_FAILURE);
			}
		}
		list = list->next;
	}
	return (0);
}

/* int	check_for_simple(t_dlist **cmd_list)
{
	t_dlist	*i_node;
	t_quote	quotes;
	t_chunk	*chunk;

	init_quotes(&quotes);
	i_node = *cmd_list;
	while (i_node && (t_chunk *)i_node->content)
	{
		chunk = (t_chunk *)i_node->content;
		if (chunk->tokens && chunk->tokens[0])
		{
			if (is_operator(chunk->tokens[0], 0, &quotes) && chunk->tokens[1])
				return (printf("bash: syntax error
					near unexpected token `%s'\n",\
					unexpected_token(i_node)), EXIT_FAILURE);

			if (is_operator(chunk->tokens[0], 0, &quotes) && !chunk->tokens[1])
				return (printf("bash: syntax
					error near unexpected token `%s'\n",\
					unexpected_token(i_node)), EXIT_FAILURE);
		}
		i_node = i_node->next;
	}
	return (0);
} */
