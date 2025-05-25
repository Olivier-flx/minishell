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

/*
bool	is_builtin(char *cmd)
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
bool is_builtin(char *cmd)
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
