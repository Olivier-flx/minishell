/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 15:40:12 by laufarin          #+#    #+#             */
/*   Updated: 2025/03/28 17:02:33 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h> //BORRAR
#include <unistd.h>//BORRAR
#include <string.h> //BORRAR
#include "../header/minishell.h"

// cc ./buildins/ft_echo.c -L./libs/libft/ -lft -g -o test2

int	ft_echo(char **args)
{
	int	i;
	int	new_line;

	i = 1;
	new_line = 1;
	while (args[i] && ft_strncmp(args[i], "-n", 2) == 0 )//para probar Cambiar ft_strcmp
	{
		new_line = 0;
		i++;
	}
	while(args[i])
	{
		printf("%s", args[i]);
		if(args[i + 1])
		{
			printf(" ");
		}
		i++;
	}
	if(new_line)
	{
		printf("\n");
	}
	return(0);
}

int	main(int argc, char **argv)
{
	char *args[] = {"echo", "-n", "-nnnnn","Hola", "mundo", "-n", NULL};
	ft_echo(args);
	return(0);

}
