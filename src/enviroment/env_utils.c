/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 20:56:46 by marvin            #+#    #+#             */
/*   Updated: 2025/04/10 20:56:46 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void ft_free_env(t_env *env)
{
    while (env)
    {
        t_env *tmp;
        
        tmp = env;
        env = env->next;
        free(tmp->key);
        free(tmp->value);
        free(tmp);
    }
}