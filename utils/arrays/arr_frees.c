/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arr_frees.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 18:19:29 by ofilloux          #+#    #+#             */
/*   Updated: 2025/04/07 16:53:23 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

//Free a full char **
void	free_av(char **av)
{
	int	i;

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

// free an av that is incomplete due to a bug
char	**free_uncomplete_av(char **av, int i)
{
	i--;
	while (i >= 0)
	{
		free(av[i]);
		i--;
	}
	free(av);
	return (NULL);
}
