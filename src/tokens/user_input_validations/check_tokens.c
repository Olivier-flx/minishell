/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 21:34:13 by ofilloux          #+#    #+#             */
/*   Updated: 2025/06/04 13:33:12 by ofilloux         ###   ########.fr       */
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
	flag = 0;
	i = 0;
	while (i_node)
	{
		if (flag == 1 && ((t_chunk *)i_node->content)->tokens[0][0] == '|')
			return (printf("bash: syntax error near unexpected token `|'\n"), EXIT_FAILURE);
		flag = 0;
		i = 0;
		while (((t_chunk *)i_node->content)->tokens[i])
			i++;
		if (i > 0 && is_operator(((t_chunk *)i_node->content)->tokens[i - 1] , 0, &quotes))
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

bool	contains_bad_var_substitution(char **tks)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (tks && tks[i])
	{
		j = 0;
		while (tks[i][j])
		{
			if (tks[i][j] == '$' && tks[i][j + 1] &&tks[i][j + 1] == '{' \
				&& tks[i][j + 2] && tks[i][j + 2] == '}')
				return (true);
			j++;
		}
		i++;
	}
	return (false);
}

bool	bad_var_substitution(t_data *data, t_dlist *cmd_list)
{
	while (cmd_list)
	{
		if (contains_bad_var_substitution(((t_chunk *)cmd_list->content)->tokens))
		{
			write (STDERR_FILENO, "-bash: ${}: bad substitution\n", 30);
			data->exit_status = 1;
			return (true);
		}
		cmd_list = cmd_list->next;
	}
	return (false);
}

// check from the last tocken to the first one
//check for redir puis pipe (check_redir_pipe)
int	check_for_user_input_error(t_data *data, t_dlist **cmd_list)
{
	if (check_for_simple(*cmd_list) > 0 \
	|| check_for_triple(cmd_list) > 0 \
	|| check_redir_pipe(cmd_list) > 0 \
	|| check_consecutive_pipes(*cmd_list) > 0 \
	|| check_pipe_is_first(*cmd_list) > 0)
	{
		data->exit_status = 2;
		return (2);
	}
	if (bad_var_substitution(data, *cmd_list))
		return (1);
	// check si accolade not closed
	if (accolade_not_closed(cmd_list) > 0) // @Util ? devrait déjà être géré par run_minishell here with line_accolade_closed()
		return (1); // @Util ?

	// check for incorrect variable name --> à gérer au niveau de l'expension

	return (0);
}
