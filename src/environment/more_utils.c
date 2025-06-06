/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 17:20:12 by marvin            #+#    #+#             */
/*   Updated: 2025/06/06 13:11:56 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	init_env_sorted(char ***array, t_env *env)
{
	int	k;

	k = 0;
	while (env)
	{
		k++;
		env = env->next;
	}
	*array = (char **)malloc((k + 1) * sizeof(char *));
	if (!(*array))
		return (-1);
	(*array)[k] = NULL;
	return (k);
}

void	sort_env(t_env **env)
{
	t_env	*start;
	int		i;

	i = 0;
	start = *env;
	while ((*env)->next)
	{
		i++;
		if ((*env)->key == NULL)
			break ;
		if ((*env)->key[0] > (*env)->next->key[0])
		{
			(*env)->next = (*env)->next->next;
			(*env)->next->next = (*env);
			if (i > 1)
				start = *env;
			(*env) = start;
		}
		else
			(*env) = (*env)->next;
	}

}

char	**env_to_sorted_array(t_env *env)
{
	char	**array;
	int		i;
	int		k;

	i = 0;
	if (!env)
		return (NULL);
	k = init_env_sorted(&array, env);
	if (!array)
		return (NULL);
	printf("___________________\n"); //@debug
	print_env_list(env);
	sort_env(&env);
	print_env_list(env);
	printf("___________________\n");
	while (env)
	{
		array[i] = ft_strjoin3(env->key, "=", env->value);
		if (!array[i])
		{
			free_uncomplete_av(&array, i);
			return (NULL);
		}
		env = env->next;
		i++;
	}
	qsort(array, k, sizeof(char *), /// @Laura
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
