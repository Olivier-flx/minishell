/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 18:10:37 by marvin            #+#    #+#             */
/*   Updated: 2025/05/04 18:00:34 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int ft_env(t_env *env)
{
	while (env)
	{
		if (env->value && env->is_exported)  // Solo imprime variables con valor
			printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
	return (0);
}
