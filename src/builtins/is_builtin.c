/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 15:31:11 by ofilloux          #+#    #+#             */
/*   Updated: 2025/05/12 21:29:47 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"


/*bool	is_builtin(char *cmd)
{
	char	**argv_cmd;
	char	*tmp;
	bool	flag;

	argv_cmd = NULL;
	tmp = cmd;
	flag = false;
	if (usr_input_got_slash(cmd))
		argv_cmd = ft_split(cmd, '/');
	if (argv_cmd && argv_cmd[0])
		tmp = argv_cmd[pp_char_len(argv_cmd) - 1];
	if (ft_strcmp(tmp, "echo") == 0 \
			|| ft_strcmp(tmp, "cd") == 0 \
			|| ft_strcmp(tmp, "pwd") == 0 \
			|| ft_strcmp(tmp, "export") == 0 \
			|| ft_strcmp(tmp, "unset") == 0 \
			|| ft_strcmp(tmp, "env") == 0 \
			|| ft_strcmp(tmp, "exit") == 0)
		flag = true;
	free_av(&argv_cmd);
	return (flag);
}*/

bool	is_builtin(char *cmd)
{
	char	**parts;
	char	*last;
	bool	flag;

	if (!cmd)
		return (false);
	// Si hay slash, dividimos en partes
	if (usr_input_got_slash(cmd))
		parts = ft_split(cmd, '/');
	else
	{
		parts = malloc(sizeof(char *) * 2);
		if (!parts)
			return (false);
		parts[0] = ft_strdup(cmd);
		parts[1] = NULL;
	}
	if (!parts || !parts[0])
		return (false);
	
	last = parts[pp_char_len(parts) - 1];

	flag = (ft_strcmp(last, "echo") == 0
		|| ft_strcmp(last, "cd") == 0
		|| ft_strcmp(last, "pwd") == 0
		|| ft_strcmp(last, "export") == 0
		|| ft_strcmp(last, "unset") == 0
		|| ft_strcmp(last, "env") == 0
		|| ft_strcmp(last, "exit") == 0);

	free_av(&parts);
	return (flag);
}


int main(void)
{

#include <stdio.h>
#include <stdbool.h>

    // Pruebas básicas (builtins directos)
    printf("=== Pruebas básicas ===\n");
    printf("echo: %d (esperado: 1)\n", is_builtin("echo"));
    printf("cd: %d (esperado: 1)\n", is_builtin("cd"));
    printf("pwd: %d (esperado: 1)\n", is_builtin("pwd"));
    printf("ls: %d (esperado: 0)\n", is_builtin("ls"));

    // Pruebas con rutas
    printf("\n=== Pruebas con rutas ===\n");
    printf("/bin/echo: %d (esperado: 1)\n", is_builtin("/bin/echo"));
    printf("./pwd: %d (esperado: 1)\n", is_builtin("./pwd"));
    printf("/usr/bin/ls: %d (esperado: 0)\n", is_builtin("/usr/bin/ls"));

    // Casos límite
    printf("\n=== Casos límite ===\n");
    printf("NULL: %d (esperado: 0)\n", is_builtin(NULL));
    printf("cadena vacía: %d (esperado: 0)\n", is_builtin(""));
    printf("echo/: %d (esperado: 1)\n", is_builtin("echo/")); // Depende de tu implementación
    printf("/bin/: %d (esperado: 0)\n", is_builtin("/bin/"));

	printf("echo////: %d (esperado: 1)\n", is_builtin("echo////"));
	printf("//////echo: %d (esperado: 1)\n", is_builtin("//////echo"));
	printf("//////echo////: %d (esperado: 1)\n", is_builtin("//////echo////"));

    return 0;
}