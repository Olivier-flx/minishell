/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 15:31:11 by ofilloux          #+#    #+#             */
/*   Updated: 2025/07/07 18:05:38 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

static void	init_tmp(char ***argv_cmd, char **tmp, char *cmd, int *flag)
{
	*argv_cmd = NULL;
	*tmp = cmd;
	*flag = -2;
}

int	get_builtin_int(char *cmd)
{
	char	**argv_cmd;
	char	*tmp;
	int		flag;

	init_tmp(&argv_cmd, &tmp, cmd, &flag);
	if (usr_input_got_slash(cmd))
		argv_cmd = ft_split(cmd, '/');
	if (argv_cmd && argv_cmd[0])
		tmp = argv_cmd[pp_char_len(argv_cmd) - 1];
	if (ft_strcmp(tmp, "echo") == 0)
		flag = 0;
	if (ft_strcmp(tmp, "cd") == 0)
		flag = 1;
	if (ft_strcmp(tmp, "pwd") == 0)
		flag = 2;
	if (ft_strcmp(tmp, "export") == 0)
		flag = 3;
	if (ft_strcmp(tmp, "unset") == 0)
		flag = 4;
	if (ft_strcmp(tmp, "env") == 0)
		flag = 5;
	if (ft_strcmp(tmp, "exit") == 0)
		flag = 6;
	free_av(&argv_cmd);
	return (flag);
}

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
