/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 20:56:46 by marvin            #+#    #+#             */
/*   Updated: 2025/04/24 14:16:03 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void ft_free_env(t_env *env)
{
	if (!env)
		return ;
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
