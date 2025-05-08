/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 17:57:53 by ofilloux          #+#    #+#             */
/*   Updated: 2025/05/08 13:04:37 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

char	**path_vect(t_env *env)
{
	char	**path_v;

	if (env == NULL)
		return (NULL);

	path_v = ft_split(ft_getenv(env, "PATH"), ':');
	return (path_v);
}

void	get_path(char *usr_cmd_input, t_exe *exec_info, t_env *env)
{
	int		i;
	char	**path_v;
	char	*test_path;
	char	*test_cmd;

	exec_info->env_path_found = false;
	path_v = path_vect(env);
	i = 0;
	while (path_v && path_v[i])
	{
		test_path = ft_strjoin(path_v[i++], "/");
		test_cmd = ft_strjoin(test_path, usr_cmd_input);
		if (access(test_cmd, X_OK) == 0)
		{
			exec_info->env_path_found = true;
			free(test_cmd);
			exec_info->env_path = test_path;
			break ;
		}
		free(test_path);
		free(test_cmd);
		exec_info->env_path = NULL;
	}
	free_av(path_v);
}
