/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_input_validation.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 15:14:36 by ofilloux          #+#    #+#             */
/*   Updated: 2025/04/22 19:12:50 by ofilloux         ###   ########.fr       */
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

/*int check_pipe_last (t_dlist **cmd_list)
{
	t_dlist	*last_node;

	last_node = find_last_node(cmd_list);
	// last_node = last_node->prev; // @debug : jai l impression qu il y a un probleme avec un noeud supplementaire vide qui s ajoute a la fin de la liste. Si cela ne cause pas de probleme en soit, cela implique que apres avoir utilise la fonction find_last_node, il fasse faire un cmd_list->prev pour avoir le dernier noeud effectif de la liste
	if (last_node && ((t_chunk *)(last_node->content))->tokens[0] \
			&& ((t_chunk *)(last_node->content))->tokens[0][0] == '|')
		return(printf("bash: syntax error near unexpected token `newline'\n"), ERROR);
	return (0);
}*/

// <> funccionna

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
	//if(check_pipe_last(cmd_list) > 0)
		//return (1);
	// check for only pipe or pipe first

	// check for empty file name


	// | sin comando despues		pipe> {waiting for cmd}

	// >\n or <\n		bash: syntax error near unexpected token `newline'

	// >>\n	or <<\n 	sh: parse error near `\n'
	return (0);
}
