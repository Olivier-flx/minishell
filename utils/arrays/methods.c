/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   methods.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 20:59:43 by ofilloux          #+#    #+#             */
/*   Updated: 2025/02/12 18:53:40 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

bool	int_var_in_arr(int var, t_int_array *arr)
{
	int	i;

	i = 0;
	if (!arr || !(arr->array) || (arr->size) < 0)
		return (false);
	while (i < arr->size)
	{
		if (var == arr->array[i])
			return (true);
		i++;
	}
	return (false);
}
