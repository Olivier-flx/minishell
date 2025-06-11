/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 15:31:11 by ofilloux          #+#    #+#             */
/*   Updated: 2025/06/09 10:11:32 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

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
