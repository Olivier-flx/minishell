/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 15:40:12 by laufarin          #+#    #+#             */
/*   Updated: 2025/07/09 20:31:43 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stdio.h>
//#include <unistd.h>
//#include <string.h>
//#include <stdlib.h>
#include "../../header/minishell.h"

// int	check_for_n(char **args, bool *new_line, int *i)
// {
// 	*i = 1;
// 	if (args[1] && ft_strcmp(args[1], "-n") == 0)
// 	{
// 		*new_line = false;
// 		*i = 2;
// 		if (args[*i] && ft_strcmp(args[*i], "-n") == 0)
// 		{
// 			write(STDERR_FILENO, "minishell: echo: ", 17);
// 			write(STDERR_FILENO, "cannot be repeated '-n'\n", 23);
// 			return (EXIT_FAILURE);
// 		}
// 	}
// 	return (EXIT_SUCCESS);
// }

int	check_for_n(char **args, bool *new_line, int *i)
{
	int	arg_len;
	int	j;

	*i = 1;
	while (args[*i] && ft_strncmp(args[*i], "-n", 2) == 0)
	{
		j = 1;
		arg_len = ft_strlen(args[*i]);
		while (args[*i][j] && j < arg_len - 1)
		{
			if (!ft_isalpha(args[*i][j]))
				return (EXIT_FAILURE);
			j++;
		}
		*new_line = false;
		(*i)++;
	}
	return (EXIT_SUCCESS);
}

int	ft_echo(t_env *env, char **args)
{
	int		i;
	bool	new_line;
	char	*home;

	new_line = true;
	if (!args || !env)
		return (EXIT_FAILURE);
	if (check_for_n(args, &new_line, &i) > 1)
		return (EXIT_FAILURE);
	while (args[i])
	{
		if (args[i][0] == '~')
		{
			home = ft_getenv(env, "HOME");
			write(STDOUT_FILENO, home, ft_strlen(home));
		}
		else
			write(STDOUT_FILENO, args[i], ft_strlen(args[i]));
		if (args[++i])
			write(STDOUT_FILENO, " ", 1);
	}
	if (new_line)
		write(STDOUT_FILENO, "\n", 1);
	return (0);
}

//cc -Wall -Wextra -Wall ./src/builtins/ft_echo.c
// ./src/enviroment/env.c ./src/enviroment/env_utils.c
// ./src/enviroment/env_search.c ./libs/libft/libft.a -lreadline -o testEcho
// int main(int ac, char **argv, char **env)
// {
// 	t_env	*env1;
// 	if (ac > 0 && env)
// 		env1 = ft_init_env(env);
// 	ft_echo(env1, argv);
// 	return (0);
// }
