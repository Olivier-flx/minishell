/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 15:40:12 by laufarin          #+#    #+#             */
/*   Updated: 2025/05/12 21:17:18 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stdio.h>
//#include <unistd.h>
//#include <string.h>
//#include <stdlib.h>
#include "../../header/minishell.h"

int	ft_echo(t_env *env, char **args)
{
	// write(STDOUT_FILENO, "DEBUG_ECHO\n", 11);  // Mensaje imposible de ignorar
	// return (0);  // Retorno simple para pruebas
	int	i = 1;
	bool	new_line = true;
	// Verifica múltiples "-n"

	if (args[1] && ft_strcmp(args[1], "-n") == 0)
	{
		new_line = false;
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
		//write(1, "y aqui!\n", 7);
/* 		if (args[i][0] == '$')
		{
			char *value = ft_getenv(env, args[i] + 1);
			if (value) write(STDOUT_FILENO, value, ft_strlen(value));
		}
		else  */if (args[i][0] == '~') {  // Opcional: soporte para ~
			char *home = ft_getenv(env, "HOME");
			write(STDOUT_FILENO, home, ft_strlen(home));
		}
		else
		{
			write(STDOUT_FILENO, args[i], ft_strlen(args[i]));
		}
		if (args[++i]) write(STDOUT_FILENO, " ", 1);
	}
	if (new_line)
		write(STDOUT_FILENO, "\n", 1);
	return (0);
}

//cc -Wall -Wextra -Wall ./src/builtins/ft_echo.c ./src/enviroment/env.c ./src/enviroment/env_utils.c ./src/enviroment/env_search.c ./libs/libft/libft.a -lreadline -o testEcho
// int main(int ac, char **argv, char **env)
// {
// 	t_env	*env1;
// 	if (ac > 0 && env)
// 		env1 = ft_init_env(env);
// 	ft_echo(env1, argv);
// 	return (0);
// }
