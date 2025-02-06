/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_frees.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 11:31:40 by ofilloux          #+#    #+#             */
/*   Updated: 2025/01/25 13:09:44 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void    free_list(t_list **stack_to_free)
{
        t_list       *next_node;

	if (*stack_to_free == NULL)
		return ;
        while (*stack_to_free != NULL)
        {
                next_node = (*stack_to_free)->next;
                free(*stack_to_free);
                *stack_to_free = next_node;
        }
        *stack_to_free = NULL;
}


//FONCTION OK
void    free_av(char **av)
{
        int     i;

	if (av == NULL)
		return ;
        i = 0;
        while (av[i] != NULL)
        {
                free(av[i]);
                i++;
        }
        free(av);
}
