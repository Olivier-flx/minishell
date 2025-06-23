/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invalid_chunks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 10:46:57 by ofilloux          #+#    #+#             */
/*   Updated: 2025/06/23 17:33:51 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../header/minishell.h"

bool	chunk_is_empty(t_chunk *chk)
{
	return (!(chk->tokens[0]));
}

bool	unique_empty_chunk(t_data *data, t_dlist *cmd_list)
{
	t_chunk	*chk;

	chk = ((t_chunk *) cmd_list->content);
	if (!cmd_list->next && chunk_is_empty(chk))
	{
		data->exit_status = 0;
		return (true);
	}
	return (false);
}

static int	print_msg(t_dlist *i_node)
{
	if (i_node->next && ((t_chunk *) i_node->next->content)->tokens \
		&& ((t_chunk *) i_node->next->content)->tokens[0])
	{
		return (printf("bash: syntax error near unexpected token `%s'\n", \
				((t_chunk *) i_node->next->content)->tokens[0]));
	}
	else
		return (printf("bash: syntax error near unexpected token `newline'\n"));
	return (0);
}

int	operator_finishes_chunk(t_dlist *cmd_list)
{
	int		i;
	t_dlist	*i_node;
	t_chunk	*chk;

	i = 0;
	i_node = cmd_list;
	while (i_node)
	{
		chk = ((t_chunk *) i_node->content);
		while (chk->tokens[i])
			i++;
		if (i > 0 && is_operator_token(chk->tokens[i - 1]))
		{
			if (print_msg(i_node) != 0)
				return (1);
		}
		i_node = i_node->next;
	}
	return (0);
}
