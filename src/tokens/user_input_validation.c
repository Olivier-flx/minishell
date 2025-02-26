/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_input_validation.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 15:14:36 by ofilloux          #+#    #+#             */
/*   Updated: 2025/02/26 18:25:45 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	check_for_triple(t_dlist **cmd_list)
{
	int		i;
	t_dlist	*i_node;

	i = 0;
	i_node = find_last_node(cmd_list);
	while(i_node)
	{
		if( ((t_input_tocken *)i_node->content)->type == OPERATOR)
			printf("operator\n");
		i_node = i_node->prev;
	}

	return(0);
}

// <> funccionna

// check from the last tocken to the first one
int	check_for_user_input_error(t_dlist **cmd_list)
{
	check_for_triple(cmd_list);
	// >>>

	// <<<

	// > >> or < <<

	// >> > or << <

	// ><

	// | sin comando despues		pipe> {waiting for cmd}

	// >\n or <\n		sh: parse error near `\n'

	// >>\n	or <<\n 	sh: parse error near `\n'
}
