/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 15:59:08 by ofilloux          #+#    #+#             */
/*   Updated: 2025/06/18 16:32:31 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

/* int	init_env_sorted(char ***array, t_env *env)
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
} */

void	swap_env_key_val(t_env *a, t_env *b)
{
	char	*tmp_key;
	char	*tmp_value;

	tmp_key = a->key;
	tmp_value = a->value;
	a->key = b->key;
	a->value = b->value;
	b->key = tmp_key;
	b->value = tmp_value;
}

void	sort_env(t_env **env)
{
	t_env	*i_node;
	t_env	*last_node_sorted;
	bool	swapped;

	if (!env || !(*env))
		return ;
	last_node_sorted = NULL;
	swapped = true;
	while (swapped)
	{
		swapped = false;
		i_node = *env;
		while (i_node->next && i_node->next != last_node_sorted)
		{
			if (i_node->key && i_node->next->key
				&& ft_strcmp(i_node->key, i_node->next->key) > 0)
			{
				swap_env_key_val(i_node, i_node->next);
				swapped = true;
			}
			i_node = i_node->next;
		}
		last_node_sorted = i_node;
	}
}

t_env	*copy_env_list(t_env *env)
{
	t_env	*cpy;
	t_env	*new_node;

	cpy = NULL;
	while (env)
	{
		new_node = ft_new_env_node(env->key, env->value, env->is_exported);
		if (!new_node)
			return (ft_free_env(cpy), NULL);
		ft_env_add_back(&cpy, new_node);
		env = env->next;
	}
	return (cpy);
}

int	print_sorted_env(t_env *env)
{
	t_env	*env_cpy;
	t_env	*head;

	env_cpy = copy_env_list(env);
	head = env_cpy;
	sort_env(&env_cpy);
	if (!env_cpy)
		return (1);
	while (env_cpy)
	{
		printf("declare -x %s=%s\n", env_cpy->key, env_cpy->value);
		env_cpy = env_cpy->next;
	}
	ft_free_env(head);
	return (0);
}
