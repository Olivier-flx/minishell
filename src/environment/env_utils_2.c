/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 17:20:12 by marvin            #+#    #+#             */
/*   Updated: 2025/06/06 16:04:49 by ofilloux         ###   ########.fr       */
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
	ft_env_add_back(env, ft_new_env_node(ft_strdup(key), \
		ft_strdup(value), true));
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
