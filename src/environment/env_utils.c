/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 20:56:46 by marvin            #+#    #+#             */
/*   Updated: 2025/05/04 18:05:02 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void ft_free_env(t_env *env)
{
	t_env *tmp;

	tmp = NULL;
	while (env)
	{
		tmp = env;
		env = env->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
	}
}

void ft_setenv(t_env **env, char *key, char *value)
{
	t_env   *current;

	current = *env;
	while(current)
	{
		if(ft_strcmp(current->key, key) == 0)
		{
			free(current->value);
			current->value = ft_strdup(value);
			return ;
		}
		current = current->next;
	}
	ft_env_add_back(env, ft_new_env_node(ft_strdup(key), ft_strdup(value), true));
}

void ft_unsetenv(t_env **env, char *key)
{
	t_env   *prev = NULL;
	t_env   *current = *env;

	while(current)
	{
		if(ft_strcmp(current->key, key) == 0)
		{
			if(prev)
				prev->next = current->next;
			else
				*env = current->next;
			free(current->key);
			free(current->value);
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}

int ft_env_size(t_env *env)
{
	int size = 0;

	while (env)
	{
		size++;
		env = env->next;
	}
	return (size);
}

char **ft_env_to_array(t_env *env)
{
	int len = ft_env_size(env);
	char **array = malloc((len + 1) * sizeof(char *));
	int i = 0;

	while (env)
	{
		array[i] = ft_strjoin3(env->key, "=", env->value);
		env = env->next;
		i++;
	}
	array[len] = NULL;
	return (array);
}

