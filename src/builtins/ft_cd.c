/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 13:34:19 by marvin            #+#    #+#             */
/*   Updated: 2025/05/12 17:40:50 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

static int update_pwds(t_env **env)
{
	char	cwd[PATH_MAX]; // @ Laura
	char	*oldpwd;

	oldpwd = ft_getenv(*env, "PWD");
	if (!getcwd(cwd, PATH_MAX)) // @ Laura
		return (perror("cd: error retrieving current directory"), 1);

	if (oldpwd)
		ft_setenv(env, "OLDPWD", oldpwd);
	ft_setenv(env, "PWD", cwd);
	return (0);
}

int ft_cd(t_env **env, char **args)
{
	char	*path;
	int	 ret;

	if (!args[1] || ft_strcmp(args[1], "~") == 0)
		path = ft_getenv(*env, "HOME");
	else if (ft_strcmp(args[1], "-") == 0)
		path = ft_getenv(*env, "OLDPWD");
	else
		path = args[1];

	if (!path)
		return (ft_putstr_fd("minishell: cd: HOME not set\n", 2), 1);
	if (access(path, F_OK) == -1)
		return (ft_putstr_fd("minishell: cd: ", 2),
				ft_putstr_fd(path, 2),
				ft_putstr_fd(": No such file or directory\n", 2), 1);
	if (chdir(path) == -1)
		return (perror("minishell: cd"), 1);

	ret = update_pwds(env);
	if (ft_strcmp(args[1], "-") == 0 && !ret)
		printf("%s\n", ft_getenv(*env, "PWD"));
	return (ret);
}
