/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 17:37:48 by ofilloux          #+#    #+#             */
/*   Updated: 2025/02/10 17:49:24 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

//return 0 if not operator, if operator return lenght
int	is_operator(char *src, int i)
{
	if (src[i] == 124)
		return(1);
	else if (src[i] == '>' && src[i + 1] && src[i + 1] == '>')
		return(2);
	else if (src[i] == '<' && src[i + 1] && src[i + 1] == '<')
		return(2);
	else if (src[i] == '<')
		return(1);
	else if (src[i] == '>')
		return(1);
	return (0);
}

// return the number of operator present in src
int	count_operador(char *src)
{
	int		in_sgl_quote;
	int		in_dbl_quote;
	int		i;
	int		op_count;

	op_count = 0;
	init_var(&in_sgl_quote, &in_dbl_quote, NULL, &i);

	if (!src)
		return (1);
	while (src[i])
	{
		if (src[i] == '"' && in_sgl_quote % 2 == 0)
			in_dbl_quote++;
		if (src[i] == '\'' && in_dbl_quote % 2 == 0)
			in_sgl_quote++;
		if (in_sgl_quote % 2 == 0  && in_dbl_quote % 2 == 0)
		{
			i += is_operator(src, i, cmd_list);
			op_count++;
			continue;
		}
		i++;
	}
	return (op_count);
}

int	get_operador_index(char *src, t_list **cmd_list)
{
	int		in_sgl_quote;
	int		in_dbl_quote;
	int		i;
	int		op_count;
	int		*operador_i;

	op_count = count_operador(src);
	init_var(&in_sgl_quote, &in_dbl_quote, NULL, &i);

	if (!src)
		return (1);
	while (src[i])
	{
		if (src[i] == '"' && in_sgl_quote % 2 == 0)
			in_dbl_quote++;
		if (src[i] == '\'' && in_dbl_quote % 2 == 0)
			in_sgl_quote++;
		//if (in_dbl_quote % 2 == 1)
		//	i += is_var_call(src, i, cmd_list);
		if (in_sgl_quote % 2 == 0  && in_dbl_quote % 2 == 0)
		{
			is_operator(src, i, cmd_list);
			op_count++;
			//i += is_var_call(src, i, cmd_list); //create seg fault
		}
		i++;
	}
	return (0);
}
