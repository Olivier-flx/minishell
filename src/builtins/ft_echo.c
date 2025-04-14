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

//#include <stdio.h> 
//#include <unistd.h>
//#include <string.h>
//#include <stdlib.h>
#include "minishell.h"

int	ft_echo(t_env *env, char **args)
{
	write(STDOUT_FILENO, "DEBUG_ECHO\n", 11);  // Mensaje imposible de ignorar
	return (0);  // Retorno simple para pruebas
	int	i = 1;
	int	new_line = 1;
	// Verifica múltiples "-n"

	write(1, "ECHO FUNCIONA!\n", 15);
	if (args[1] && ft_strcmp(args[1], "-n") == 0)
	{
		new_line = 0;
		i = 2;
		if (args[i] && ft_strcmp(args[i], "-n") == 0)
		{
			write(STDERR_FILENO, "minishell: echo: ", 17);
			write(STDERR_FILENO, "cannot be repeated '-n'\n", 23);
			return (1);
		}
	}
// Imprime argumentos
	while (args[i])
	{
		write(1, "y aqui!\n", 7);
		if (args[i][0] == '$')
		{
			char *value = ft_getenv(env, args[i] + 1);
			if (value) write(STDOUT_FILENO, value, ft_strlen(value));
		}
		else if (args[i][0] == '~') {  // Opcional: soporte para ~
			char *home = ft_getenv(env, "HOME");
			write(STDOUT_FILENO, home, ft_strlen(home));
		}
		else
		{
			write(STDOUT_FILENO, args[i], ft_strlen(args[i]));
		}
		if (args[++i]) write(STDOUT_FILENO, " ", 1);
	}
	/*if (!new_line)
        write(STDOUT_FILENO, "\n", 1);
	else
	{
		write(STDOUT_FILENO, " ", 1);   // Espacio final si es -n (para no pegarse al prompt)
	}*/
	if (!new_line)
	{
		write(1, "PERO AQUI?!\n", 11);
		write(STDOUT_FILENO, "\n¡NUEVO SALTO!\n", 15);  // Texto visible
	}
	else
	{
		write(STDOUT_FILENO, " ¡ESPACIO! ", 11);  // Texto visible
	}
	return (0);
}