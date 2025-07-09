/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 09:32:58 by ofilloux          #+#    #+#             */
/*   Updated: 2025/07/09 14:57:33 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

//PATH_MAX from limits.h
static int	update_pwds(t_env **env)
{
	char	cwd[PATH_MAX];
	char	*oldpwd;

	oldpwd = ft_getenv(*env, "PWD");
	if (!getcwd(cwd, PATH_MAX))
		return (perror("cd: error retrieving current directory"), \
		write(STDERR_FILENO, ": getcwd: ", 11), \
		ft_putstr_fd(strerror(errno), 2), \
		write(STDERR_FILENO, "\n", 1), 1);
	if (oldpwd)
		ft_setenv(env, "OLDPWD", oldpwd);
	ft_setenv(env, "PWD", cwd);
	return (0);
}

int	ft_cd(t_env **env, char **args)
{
	char	*path;
	int		ret;

	if (!args[1] || ft_strcmp(args[1], "~") == 0)
		path = ft_getenv(*env, "HOME");
	else if (ft_strcmp(args[1], "-") == 0)
		path = ft_getenv(*env, "OLDPWD");
	else
		path = args[1];
	if (!path)
		return (ft_putstr_fd("minishell: cd: HOME not set\n", 2), 1);
	if (access(path, F_OK) == -1)
		return (ft_putstr_fd("minishell: cd: ", 2), \
			ft_putstr_fd(path, 2), \
			ft_putstr_fd(": No such file or directory\n", 2), 1);
	if (chdir(path) == -1)
		return (perror("minishell: cd"), 1);
	ret = update_pwds(env);
	if (args[1] && ft_strcmp(args[1], "-") == 0 && !ret)
		printf("%s\n", ft_getenv(*env, "PWD"));
	return (ret);
}
