/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator_arr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 16:37:22 by ofilloux          #+#    #+#             */
/*   Updated: 2025/05/14 16:43:32 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

// return the number of operator present in src
int	count_operador(char *src)
{
	t_quote	quote;
	int		i;
	int		tmp;
	int		op_count;

	init_operador_var(&quote, &op_count, &i);
	if (!src)
		return (1);
	while (src[i])
	{
		if (src[i] == '"' && quote.dbl_quote % 2 == 0)
			quote.dbl_quote++;
		if (src[i] == '\'' && quote.dbl_quote % 2 == 0)
			quote.dbl_quote++;
		tmp = is_operator(src, i, &quote);
		if (tmp > 0)
		{
			i += tmp;
			op_count++;
			continue ;
		}
		i++;
	}
	return (op_count);
}

static void	fill_operator_positions(char *src, t_int_array *arr)
{
	t_quote	quote;
	int		op_count;
	int		i;
	int		j;

	j = 0;
	init_operador_var(&quote, &op_count, &i);
	while (src[i++])
	{
		quote_increment(src, i, &quote);
		op_count = is_operator(src, i, &quote);
		if (op_count > 0)
		{
			arr->array[j++] = i;
			if (op_count == 2)
				arr->array[j++] = i + 1;
			i += op_count;
			continue ;
		}
		i++;
	}
}

//fill the array on indexes of char that are operators in src
void	set_ope_char_i_arr(char *src, t_int_array *arr)
{
	if (arr->size == 0)
		return ;
	arr->array = malloc(arr->size * sizeof(int));
	if (!arr->array)
		return ;
	fill_operator_positions(src, arr);
}

//calculate the lenght of the array on indexes of char that are operators in src
void	set_ope_char_i_struc_arr(char *src, t_int_array *arr)
{
	int		op_count;
	int		i;
	t_quote	quote;
	int		tmp;

	tmp = 0;
	init_operador_var(&quote, &op_count, &i);
	while (src[i])
	{
		quote_increment(src, i, &quote);
		tmp = is_operator(src, i, &quote);
		if (tmp > 0)
		{
			op_count += tmp;
			i += tmp;
			continue ;
		}
		i++;
	}
	arr->size = op_count;
	set_ope_char_i_arr(src, arr);
}
