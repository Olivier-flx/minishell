/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arr_frees.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 18:19:29 by ofilloux          #+#    #+#             */
/*   Updated: 2025/05/10 16:32:34 by ofilloux         ###   ########.fr       */
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
		ft_free((void **) &av[i]);
		i++;
	}
	ft_free((void **) &av);
}

// free an av that is incomplete due to a bug
char	**free_uncomplete_av(char **av, int i)
{
	i--;
	while (i >= 0)
	{
		ft_free((void **) &av[i]);
		i--;
	}
	ft_free((void **) &av);
	return (NULL);
}
