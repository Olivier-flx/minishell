/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_search.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 21:20:00 by marvin            #+#    #+#             */
/*   Updated: 2025/04/19 10:43:47 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "builtins.h"

#include "../../header/minishell.h"

char *ft_getenv(t_env *env, char *key)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
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
