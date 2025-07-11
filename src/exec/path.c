/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 17:57:53 by ofilloux          #+#    #+#             */
/*   Updated: 2025/07/11 18:09:17 by ofilloux         ###   ########.fr       */
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

void	get_path(char *usr_cmd_input, t_chunk *chnk, t_env *env)
{
	int		i;
	char	**path_v;
	char	*test_path;
	char	*test_cmd;

	path_v = path_vect(env);
	i = 0;
	while (path_v && path_v[i])
	{
		test_path = ft_strjoin(path_v[i++], "/");
		test_cmd = ft_strjoin(test_path, usr_cmd_input);
		if (access(test_cmd, X_OK) == 0)
		{
			ft_free((void **) &test_cmd);
			chnk->bin_path = test_path;
			break ;
		}
		ft_free((void **) &test_path);
		ft_free((void **) &test_cmd);
		chnk->bin_path = NULL;
	}
	free_av(&path_v);
}
// void	get_path(char *usr_cmd_input, t_exe *exe_nfo, t_env *env)
// {
// 	int		i;
// 	char	**path_v;
// 	char	*test_path;
// 	char	*test_cmd;

// 	exe_nfo->env_path_found = false;
// 	path_v = path_vect(env);
// 	i = 0;
// 	while (path_v && path_v[i])
// 	{
// 		test_path = ft_strjoin(path_v[i++], "/");
// 		test_cmd = ft_strjoin(test_path, usr_cmd_input);
// 		if (access(test_cmd, X_OK) == 0)
// 		{
// 			exe_nfo->env_path_found = true;
// 			ft_free((void **) &test_cmd);
// 			exe_nfo->env_path = test_path;
// 			break ;
// 		}
// 		ft_free((void **) &test_path);
// 		ft_free((void **) &test_cmd);
// 		exe_nfo->env_path = NULL;
// 	}
// 	free_av(&path_v);
// }
