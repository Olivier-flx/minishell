/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 11:53:38 by marvin            #+#    #+#             */
/*   Updated: 2025/06/23 18:12:51 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

static int	is_valid_export(char *arg)
{
	if (!is_valid_env_key(arg))
	{
		ft_putstr_fd("minishell: export: `", STDERR_FILENO);
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putstr_fd("`: not a valid identifier\n", STDERR_FILENO);
		return (0);
	}
	return (1);
}

static int	process_export_arg(t_env **env, char *arg)
{
	char	*key_value;
	char	*equal_sign;
	char	*key;
	char	*value;

	key_value = ft_strdup(arg);
	if (!key_value)
		return (1);
	equal_sign = ft_strchr(key_value, '=');
	key = key_value;
	value = NULL;
	if (equal_sign && ft_strlen(key_value) > 1)
	{
		*equal_sign = '\0';
		value = equal_sign + 1;
	}
	if (!is_valid_export(key))
	{
		ft_free((void **) &key_value);
		return (1);
	}
	update_or_add_env(env, key, value);
	ft_free((void **) &key_value);
	return (0);
}

int	ft_export(t_env **env, char **args)
{
	int	i;
	int	status;

	if (!env || !args)
		return (1);
	i = 1;
	if (!args[i])
		return (print_sorted_env(*env));
	status = 0;
	while (args[i])
	{
		if (process_export_arg(env, args[i]))
			status = 1;
		i++;
	}
	return (status);
}
