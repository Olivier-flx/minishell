/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   methods.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 20:59:43 by ofilloux          #+#    #+#             */
/*   Updated: 2025/02/22 10:43:05 by ofilloux         ###   ########.fr       */
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

void	print_int_arr(t_int_array *arr)
{
	int	i;

	i = 0;
	while (i < arr->size)
	{
		printf("print_arr[%i] = %i\n", i, arr->array[i]);
		i++;
	}
}

void	print_pp_char_arr(char **str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		printf("*str[%i] = `%s`\n", i, str[i]);
		i++;
	}
}
