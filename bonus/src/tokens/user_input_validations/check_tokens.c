/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 21:34:13 by ofilloux          #+#    #+#             */
/*   Updated: 2025/06/20 16:48:05 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

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

// check from the last tocken to the first one
//check for redir puis pipe (check_redir_pipe)
int	check_for_user_input_error(t_data *data, t_dlist **cmd_list) //@BONUS CHUNKS  && and ||
{
	if (unique_empty_node(data, *cmd_list))
		return (3);
	if (check_for_simple(*cmd_list) > 0 \
	|| check_for_triple(cmd_list) > 0 \
	 //@BONUS CHUNKS  && and ||
	|| check_redir_pipe(cmd_list) > 0 \
	//@BONUS CHUNKS  && and ||
	|| check_consecutive_pipes(*cmd_list) > 0 \
	|| check_pipe_is_first(*cmd_list) > 0)
	{
		data->exit_status = 2;
		return (2);
	}
	if (bad_var_substitution(data, *cmd_list))
		return (1);
	if (accolade_not_closed(cmd_list) > 0)
		return (1);
	return (0);
}
