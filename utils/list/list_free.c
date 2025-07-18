/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 13:11:48 by ofilloux          #+#    #+#             */
/*   Updated: 2025/06/04 13:11:49 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	free_list(t_dlist *stack_to_free)
{
	t_dlist	*next_node;

	if (stack_to_free == NULL)
		return ;
	while (stack_to_free != NULL)
	{
		next_node = (stack_to_free)->next;
		ft_free((void **) &stack_to_free);
		stack_to_free = next_node;
	}
	stack_to_free = NULL;
}

void	free_list1(t_dlist **stack_to_free)
{
	t_dlist	*next_node;

	if (*stack_to_free == NULL)
		return ;
	while (*stack_to_free != NULL)
	{
		next_node = (*stack_to_free)->next;
		ft_free((void **)stack_to_free);
		*stack_to_free = next_node;
	}
	*stack_to_free = NULL;
}
