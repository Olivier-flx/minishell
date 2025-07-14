/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 17:20:12 by marvin            #+#    #+#             */
/*   Updated: 2025/07/14 21:39:09 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	update_or_add_env(t_env **env, char *key, char *value)
{
	t_env	*current;

	current = *env;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			ft_free((void **) &current->value);
			current->value = ft_strdup(value);
			return ;
		}
		current = current->next;
	}
	ft_env_add_back(env, ft_new_env_node(key, value, true));
}

int	is_valid_env_key(char *key)
{
	if (!key || !*key || ft_isdigit(*key))
		return (0);
	while (*key)
	{
		if (!ft_isalnum(*key) && *key != '_')
			return (0);
		key++;
	}
	return (1);
}

static void	update_env(t_env *env_list)
{
	int		tmp;
	char	*str;

	tmp = 0;
	tmp = ft_atoi(ft_getenv(env_list, "SHLVL"));
	tmp++;
	str = ft_itoa(tmp);
	update_or_add_env(&env_list, "SHLVL", str);
	ft_free((void **) &str);
}

void	is_minishell(t_data *data, char *arg_0)
{
	char	**av;
	char	*tmp;

	if (!arg_0)
		return ;
	av = ft_split(arg_0, '/');
	if (av && av[0])
	{
		tmp = av[pp_char_len(av) - 1];
		if (ft_strcmp(tmp, "minishell") == 0)
			update_env(data->env_list);
	}
	free_av(&av);
}
