/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laufarin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 19:48:00 by laufarin          #+#    #+#             */
/*   Updated: 2025/02/14 20:36:51 by laufarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	int	i;
	(void)av; // Ignorar `av` de momento
	(void)ac;

	i = 0;
//	if(ac > 1)
	while(env[i] != NULL)
	{
		printf("%s\n", env[i]);
		i++;
	}
	return(0);
}
