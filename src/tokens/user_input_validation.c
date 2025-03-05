/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_input_validation.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 15:14:36 by ofilloux          #+#    #+#             */
/*   Updated: 2025/03/05 18:23:01 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

// check for >>> or <<< or << < or >> > or < << or > >>
// or ><
int	check_for_triple(t_dlist **cmd_list)
{
	t_dlist	*i_node;
	t_chunk *chunk;
	int		flag;
	char	*tmp;

	flag = 0;
	i_node = find_last_node(cmd_list);
	chunk = NULL;
	tmp = NULL;
	while(i_node)
	{
		chunk = (t_chunk *)i_node->content;
		if(chunk && chunk->type == OPERATOR)
		{
			if (chunk->content && chunk->content[0] &&chunk->content[0][0])
			{
				if (1 == flag && tmp && tmp[0] == '<' && chunk->content[0][0] == '>')
					return(printf("bash: syntax error near unexpected token `%s'\n", tmp));
				if (1 == flag && chunk->content[0][0] =='>')
					return(printf("bash: syntax error near unexpected token `%s'\n", tmp));
				if (1 == flag && chunk->content[0][0] =='<')
					return(printf("bash: syntax error near unexpected token `%s'\n", tmp));
				tmp = chunk->content[0];
			}
			flag = 1;
		}
		else
			flag = 0;
		i_node = i_node->prev;
	}
	return(0);
}

// <> funccionna

// check from the last tocken to the first one
int	check_for_user_input_error(t_dlist **cmd_list)
{
	if (check_for_triple(cmd_list) > 0)
		return (1);
	// >>>

	// <<<

	// > >> or < <<

	// >> > or << <

	// ><

	// | sin comando despues		pipe> {waiting for cmd}

	// >\n or <\n		sh: parse error near `\n'

	// >>\n	or <<\n 	sh: parse error near `\n'
	return (0);
}
