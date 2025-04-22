/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_input_validation.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 15:14:36 by ofilloux          #+#    #+#             */
/*   Updated: 2025/04/22 11:36:53 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

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

	// check for only pipe or pipe first

	// check for empty file name


	// | sin comando despues		pipe> {waiting for cmd}

	// >\n or <\n		bash: syntax error near unexpected token `newline'

	// >>\n	or <<\n 	sh: parse error near `\n'
	return (0);
}
