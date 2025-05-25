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
}
*/
/*bool is_builtin(char *cmd)
{
    if (!cmd)
        return (false);

    // Extraer nombre base del comando (manejo de paths)
    char *base_cmd = cmd;
    char *last_slash = cmd;
    while (*last_slash)
	{
        if (*last_slash == '/')
            base_cmd = last_slash + 1;
        last_slash++;
    }
    return (
        ft_strcmp(base_cmd, "echo") == 0 ||
        ft_strcmp(base_cmd, "cd") == 0 ||
        ft_strcmp(base_cmd, "pwd") == 0 ||
        ft_strcmp(base_cmd, "export") == 0 ||
        ft_strcmp(base_cmd, "unset") == 0 ||
        ft_strcmp(base_cmd, "env") == 0 ||
        ft_strcmp(base_cmd, "exit") == 0
    );
}*/

bool is_builtin(char *cmd)
{
    if (!cmd || !*cmd)
        return false;

    // Encontrar el último segmento después de la última '/'
    char *base = cmd;
    char *last_slash = ft_strrchr(cmd, '/');
    if (last_slash)
        base = last_slash + 1;

    // Calcular longitud ignorando '/' finales
    size_t len = 0;
    while (base[len] && base[len] != '/')
        len++;

    // Comparación exacta con builtins
    if (len == 4 && !ft_strncmp(base, "echo", 4)) return true;
    if (len == 2 && !ft_strncmp(base, "cd", 2)) return true;
    if (len == 3 && !ft_strncmp(base, "pwd", 3)) return true;
    if (len == 6 && !ft_strncmp(base, "export", 6)) return true;
    if (len == 5 && !ft_strncmp(base, "unset", 5)) return true;
    if (len == 3 && !ft_strncmp(base, "env", 3)) return true;
    if (len == 4 && !ft_strncmp(base, "exit", 4)) return true;

    return false;
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

/*static bool	is_builtin_cmd(char *cmd)
{
	return (ft_strcmp(cmd, "echo") == 0
		|| ft_strcmp(cmd, "cd") == 0
		|| ft_strcmp(cmd, "pwd") == 0
		|| ft_strcmp(cmd, "export") == 0
		|| ft_strcmp(cmd, "unset") == 0
		|| ft_strcmp(cmd, "env") == 0
		|| ft_strcmp(cmd, "exit") == 0);
}
flag = is_builtin_cmd(tmp);

*/
