/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_input_validation.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 15:14:36 by ofilloux          #+#    #+#             */
/*   Updated: 2025/05/06 10:03:40 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

//verifica que un Pipe no sea directamente despues de una redireccion
int	check_redir_pipe(t_dlist **cmd_list)
{
	t_dlist	*i_node;
	int		i;
	int flag;
	t_quote	quotes;

	init_quotes(&quotes);
	i_node = *cmd_list;
	flag = 0;
	i = 0;
	while(i_node)
	{
		if (flag == 1 && ((t_chunk *)i_node->content)->tokens[0][0] == '|')
			return(printf("bash: syntax error near unexpected token `|'\n"), ERROR);
		flag = 0;
		i = 0;
		while (((t_chunk *)i_node->content)->tokens[i])
			i++;
		if(i > 0 && is_operator(((t_chunk *)i_node->content)->tokens[i - 1] , 0, &quotes))
			flag = 1;
		i_node = i_node->next;
	}
	return(SUCCESS);
}

int check_pipe_last (t_dlist **cmd_list)
{
	t_dlist	*last_node;

	last_node = find_last_node(cmd_list);
	// last_node = last_node->prev; // @debug : jai l impression qu il y a un probleme avec un noeud supplementaire vide qui s ajoute a la fin de la liste. Si cela ne cause pas de probleme en soit, cela implique que apres avoir utilise la fonction find_last_node, il fasse faire un cmd_list->prev pour avoir le dernier noeud effectif de la liste
	if (last_node && ((t_chunk *)(last_node->content))->tokens[0] \
			&& ((t_chunk *)(last_node->content))->tokens[0][0] == '|')
		return(printf("bash: syntax error near unexpected token `newline'\n"), ERROR);
	return (0);
}


int	line_accolade_closed(char *line)
{
	int		i;
	t_quote	quotes;
	int		flag_acc;
	int		flag_var;

	i = -1;
	init_quotes(&quotes);
	flag_acc = 0;
	flag_var = 0;
	while (line[++i])
	{
		quote_increment(line, i, &quotes);
		if (line[i] == '$' && quote_are_closed(&quotes))
			flag_var = 1;
		if (1 == flag_var && line[i] == '{')
			flag_acc = 1;
		// if (flag_acc == 1 && line[i] != '{' && line[i] != '}')
		// 	k++;
		if (flag_acc == 1 && line[i] == '}')
		{
			flag_var = 0;
			flag_acc = 0;
		}
	}
	return (flag_acc == 0);
}

// <> funccionna
int	check_tocken_accolade(char *token)
{
	int		i;
	t_quote	quotes;
	int		flag_acc;
	int		flag_var;

	init_quotes(&quotes);
	i = -1;
	flag_acc = 0;
	flag_var = 0;
	while (token[++i])
	{
		quote_increment(token, i, &quotes);
		if(token[i] == '$' && quote_are_closed(&quotes))
			flag_var = 1;
		if (1 == flag_var && token[i] == '{')
			flag_acc = 1;
		// if (flag_acc == 1 && token[i] != '{' && token[i] != '}')
		// 	k++;
		if (flag_acc == 1 && token[i] == '}')
		{
			flag_var = 0;
			flag_acc = 0;
		}
	}
	return (!(flag_acc == 0));
}

int	accolade_not_closed(t_dlist **cmd_list)
{
	t_dlist	*i_node;
	int		i;
	int flag;

	i_node = *cmd_list;
	flag = 0;
	while(i_node)
	{
		i = 0;
		while (((t_chunk *)i_node->content)->tokens[i] && flag > 1)
		{
			flag = check_tocken_accolade(((t_chunk *)i_node->content)->tokens[i++]);
			if(flag > 0)
				return (ERROR);
		}
		i_node = i_node->next;
	}
	return (SUCCESS);
}

// check from the last tocken to the first one
int	check_for_user_input_error(t_dlist **cmd_list)
{
	if (check_for_simple(cmd_list) > 0)
		return (1);
	if (check_for_triple(cmd_list) > 0)
		return (1);
	//check for redir puis pipe
	if(check_redir_pipe(cmd_list) > 0)
		return (1);
	if(check_pipe_last(cmd_list) > 0)
		//return (1);
	// check si accolade not closed
	if(accolade_not_closed(cmd_list) > 0) // @Util ? devrait déjà être géré par run_minishell here with line_accolade_closed()
		return (1); // @Util ?

	// check for incorrect variable name --> à gérer au niveau de l'expension

	return (0);
}
