/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_separators.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 17:37:48 by ofilloux          #+#    #+#             */
/*   Updated: 2025/03/30 17:57:34 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

// @info : return the len of the delimiter OR 0 if not a delimiter
int	is_seperator(char *src, int i, t_quote *quote)
{
	if (quote->sgl % 2 == 0  && quote->dbl % 2 == 0)
	{
		if (src[i] == '>' && src[i + 1] && src[i + 1] == '>')
			return(2);
		else if (src[i] == '<' && src[i + 1] && src[i + 1] == '<')
			return(2);
		else if (src[i] == 124)
			return(1);
		else if (src[i] == '<')
			return(1);
		else if (src[i] == '>')
			return(1);
		else if (src[i] == ' ')
			return (1);
	}
	return (0);
}

//fill the array on indexes of char that are operators in src
void	set_separator_char_i_arr(char *src, t_int_array *arr)
{
	int			op_count;
	int			i;
	int			j;
	t_quote		quote;

	j = 0;
	if (arr->size == 0)
		return ;
	arr->array = malloc (arr->size * sizeof(int));
	if (!(arr->array))
		return ;
	init_operador_var(&quote, &op_count, &i);
	while (src[i])
	{
		quote_increment(src, i, &quote);
		op_count = is_seperator(src, i, &quote);
		if (op_count > 0)
		{
			arr->array[j++] = i;
			//if (op_count == 2)
			//	arr->array[j++] = i + 1;
			i += op_count;
			continue ;
		}
		i++;
	}
	i = 0;
}

//calculate the lenght of the array on indexes of char that are operators in src
void	set_separator_char_i_struc_arr(char *src, t_int_array *arr)
{
	int			op_count;
	int			i;
	t_quote		quote;
	int			tmp;

	tmp = 0;
	init_operador_var(&quote, &op_count, &i);
	while (src[i])
	{
		quote_increment(src, i, &quote);
		tmp = is_seperator(src, i, &quote);
		if (tmp > 0)
		{
			op_count++;
			i += tmp;
			continue ;
		}
		i++;
	}
	arr->size = op_count;
	set_separator_char_i_arr(src, arr);
}
