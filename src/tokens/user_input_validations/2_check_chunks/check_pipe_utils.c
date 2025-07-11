/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pipe_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 13:32:44 by ofilloux          #+#    #+#             */
/*   Updated: 2025/07/11 17:47:09 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../header/minishell.h"

bool	is_pipe_chunk(t_chunk *chunk)
{
	return (chunk && chunk->tokens \
		&& chunk->tokens[0] \
		&& chunk->tokens[0][0] == '|' \
		&& chunk->tokens[0][1] == '\0');
}

//verifica que un Pipe no sea directamente despues de una redireccion
int	check_redir_pipe(t_dlist **cmd_list)
{
	t_dlist	*i_node;
	int		i;
	int		flag;
	t_quote	quotes;

	init_quotes(&quotes);
	i_node = *cmd_list;
	init_i_j(&i, &flag);
	while (i_node)
	{
		if (flag == 1 && ((t_chunk *)i_node->content)->tokens[0][0] == '|')
			return (printf("bash: syntax error near unexpected token `|'\n"), \
				EXIT_FAILURE);
		init_i_j(&i, &flag);
		while (((t_chunk *)i_node->content)->tokens[i])
			i++;
		if (i > 0 && is_operator(((t_chunk *)i_node->content)->tokens[i - 1] \
			, 0, &quotes))
			flag = 1;
		i_node = i_node->next;
	}
	return (EXIT_SUCCESS);
}

int	check_pipe_is_first(t_dlist *list)
{
	if (!list)
		return (1);
	if (is_pipe_chunk((t_chunk *)list->content))
		return (printf("bash: syntax error near unexpected token `|'\n"));
	return (0);
}
/* 	t_dlist	*last_node;

	last_node = find_last_d_node(cmd_list);
	// last_node = last_node->prev; // @debug :
	 jai l impression qu il y a un probleme avec un noeud supplementaire
	  vide qui s ajoute a la fin de la liste. Si cela ne cause pas de
	   probleme en soit, cela implique que apres avoir utilise
	   la fonction find_last_node, il fasse faire un cmd_list->prev
	   pour avoir le dernier noeud effectif de la liste
	if (last_node && ((t_chunk *)(last_node->content))->tokens[0] \
			&& ((t_chunk *)(last_node->content))->tokens[0][0] == '|')
		return (printf("bash: syntax error near
		unexpected token `newline'\n"), EXIT_FAILURE);
	return (0); */

int	check_consecutive_pipes(t_dlist *cmd_list)
{
	int		count;

	while (cmd_list)
	{
		if (is_pipe_chunk((t_chunk *)cmd_list->content))
		{
			count = 1;
			while (cmd_list->next && \
				is_pipe_chunk((t_chunk *)cmd_list->next->content))
			{
				count++;
				cmd_list = cmd_list->next;
			}
			if (count > 1)
			{
				printf("bash: syntax error near unexpected token `|'\n");
				return (EXIT_FAILURE);
			}
		}
		cmd_list = cmd_list->next;
	}
	return (EXIT_SUCCESS);
}
