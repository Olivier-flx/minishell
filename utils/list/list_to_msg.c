/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_to_msg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 16:51:49 by ofilloux          #+#    #+#             */
/*   Updated: 2025/02/17 15:54:09 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	print_dlist(t_dlist **list)
{
	t_dlist	*i_node;
	//char	*to_print;
	int		i;

	i = 0;
	i_node = *list;
	while (i_node)
	{
		if (i_node->content)
		{
			while (((t_input_tocken *)i_node->content)->content[i])
				printf("`%s`\n", ((t_input_tocken *)i_node->content)->content[i++]);
		}
		//else
		//	printf("Error: content is NULL in node.\n");
		i_node = i_node->next;
	}
}
