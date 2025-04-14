/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_search.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 21:20:00 by marvin            #+#    #+#             */
/*   Updated: 2025/04/10 21:20:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"builtins.h"

#include "minishell.h"

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