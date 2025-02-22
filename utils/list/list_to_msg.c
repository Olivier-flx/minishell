/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_to_msg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 16:51:49 by ofilloux          #+#    #+#             */
/*   Updated: 2025/02/22 10:51:09 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	print_dlist(t_dlist **list)
{
	t_dlist	*i_node;
	//char	*to_print;
	int		i;
	int		j;

	i = 0;
	j = 0;
	i_node = *list;
	while (i_node)
	{
		if (i_node->content)
		{
			printf("chunk numero %i = ", j);
			j++;
			fflush(stdout);
			i = 0;
			while (((t_input_tocken *)i_node->content)->content[i])
			{
				printf("`%s`;", ((t_input_tocken *)i_node->content)->content[i++]);
				fflush(stdout);
			}
			printf("\n");
			fflush(stdout);
		}
		//else
		//	printf("Error: content is NULL in node.\n");
		i_node = i_node->next;
	}
}
