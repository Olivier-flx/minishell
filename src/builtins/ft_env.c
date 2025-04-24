/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 18:10:37 by marvin            #+#    #+#             */
/*   Updated: 2025/04/14 18:10:37 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "minishell.h"

int ft_env(t_env *env)
{
    while (env)
    {
        if (env->value)  // Solo imprime variables con valor
            printf("%s=%s\n", env->key, env->value);
        env = env->next;
    }
    return (0);
}