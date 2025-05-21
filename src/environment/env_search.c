/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_search.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 21:20:00 by marvin            #+#    #+#             */
/*   Updated: 2025/05/21 16:47:40 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "builtins.h"

#include "../../header/minishell.h"

char *ft_getenv(t_env *env, char *key)
{
	if (!key)
		return (NULL);
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0 && env->is_exported == true)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

// Función extra opcional
int ft_env_exists(t_env *env, char *key)
{
	return (ft_getenv(env, key) != NULL);
}
