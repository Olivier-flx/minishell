/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_to_msg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 16:51:49 by ofilloux          #+#    #+#             */
/*   Updated: 2025/02/07 17:19:37 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	print_list(t_list **list)
{
	t_list	*i_node;

	i_node = *list;
	while (i_node)
	{
		if (i_node->content)
			printf("%s\n", ((t_input_tocken *)i_node->content)->content);
		else
			printf("Error: content is NULL in node.\n");
		i_node = i_node->next;
	}
}
