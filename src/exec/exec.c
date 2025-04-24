/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
<<<<<<<< HEAD:src/exec/exec.c
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 19:29:28 by ofilloux          #+#    #+#             */
/*   Updated: 2025/04/22 19:29:30 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

========
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 20:56:46 by marvin            #+#    #+#             */
/*   Updated: 2025/04/19 16:42:19 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/builtins.h"

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
>>>>>>>> laura:src/enviroment/env_utils.c
