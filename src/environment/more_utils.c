/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 17:20:12 by marvin            #+#    #+#             */
/*   Updated: 2025/06/06 12:05:49 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

char **env_to_sorted_array(t_env *env)
{
	int		count = 0;
	t_env   *tmp = env;
	char	**array;
	int	 i = 0;

	if (!env)
		return NULL;
	while (tmp && ++count)
		tmp = tmp->next;
	array = (char **)malloc((count + 1) * sizeof(char *));
	if (!array)
		return (NULL);
	tmp = env;
	while (tmp)
	{
		array[i] = ft_strjoin3(tmp->key, "=", tmp->value);
		if (!array[i])
		{
			while (--i >= 0)
				free(array[i]);
			free(array);
			return (NULL);
		}
		tmp = tmp->next;
		i++;
	}
	array[count] = NULL;
	qsort(array, count, sizeof(char *), /// @Laura
		(int (*)(const void *, const void *))ft_strcmp);

	return (array);
}

int	print_sorted_env(t_env *env)
{
	char	**env_sorted;
	int		i;

	env_sorted = env_to_sorted_array(env);
	i = 0;
	if (!env)
		return (0);
	if (!env_sorted)
		return (1);
	while (env_sorted[i])
	{
		printf("declare -x %s\n", env_sorted[i]);
		ft_free((void **) &(env_sorted[i]));
		i++;
	}
	ft_free((void **) env_sorted);
	return (0);
}

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
