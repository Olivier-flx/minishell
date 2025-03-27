/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laufarin <laufarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 15:40:12 by laufarin          #+#    #+#             */
/*   Updated: 2025/03/27 17:19:32 by laufarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h> //BORRAR
#include <unistd.h>//BORRAR
#include <string.h> //BORRAR

int	ft_echo(char **args)
{
	int	i;
	int	new_line;

	i = 1;
	new_line = 1;
	if (args[1] && ft_strcmp(args[1], "-n") == 0 )//para probar Cambiar ft_strcmp
	{
		new_line = 0;
		i = 2;
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
/*
int	main(int argc, char **argv)
{
	char *args[] = {"echo", "Hola", "mundo", NULL};	
	ft_echo(args);
	return(0);

}*/
