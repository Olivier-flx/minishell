/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 17:37:48 by ofilloux          #+#    #+#             */
/*   Updated: 2025/05/01 15:08:12 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

//return 0 if not operator, if operator return lenght
int	is_operator(char *src, int i, t_quote *quote)
{
	if (!quote)
		init_quotes(quote);
	if (quote->dbl_quote % 2 == 0  && quote->dbl_quote % 2 == 0)
	{
		if (src[i] == '>' && src[i + 1] && src[i + 1] == '>')
			return(2);
		else if (src[i] == '<' && src[i + 1] && src[i + 1] == '<')
			return(2);
		//else if (src[i] == 124) // @debug pose probleme avec init_redir_arr_and_files
		//	return(1);
		else if (src[i] == '<')
			return(1);
		else if (src[i] == '>')
			return(1);
	}
	return (0);
}


int	is_redirection(char *src, int i, t_quote *quote)
{
	if (quote->dbl_quote % 2 == 0  && quote->dbl_quote % 2 == 0)
	{
		if (src[i] == '>' && src[i + 1] && src[i + 1] == '>')
			return(2);
		else if (src[i] == '<' && src[i + 1] && src[i + 1] == '<')
			return(2);
		else if (src[i] == '<')
			return(1);
		else if (src[i] == '>')
			return(1);
	}
	return (0);
}


////// NOT USED /////
// void	set_operator_info(char *src, int i, t_operator	*operador_data, int *op_count)
// {
// 	*operador_data->index = i;
// 	if (src[i] == '>' && src[i + 1] && src[i + 1] == '>')
// 		*operador_data->operator = ft_strdup(">>");
// 	else if (src[i] == '<' && src[i + 1] && src[i + 1] == '<')
// 		*operador_data->operator = ft_strdup("<<");
// 	else if (src[i] == 124)
// 		*operador_data->operator = ft_strdup("|");
// 	else if (src[i] == '<')
// 		*operador_data->operator = ft_strdup("<");
// 	else if (src[i] == '>')
// 		*operador_data->operator = ft_strdup(">");
// 	*operador_data->len = ft_strlen(operador_data->operator);
// 	*op_count++;
// }


void	init_operador_var(t_quote *quote, int *op_count, int *i)
{
	init_quotes(quote);
	//if (op_count)
	//{
		*op_count = 0;
	//}
	//if (i)
		*i = 0;
}

// return the number of operator present in src
int	count_operador_from_pp_char(char **content)
{
	int		i;
	int		k;
	t_quote	quote;

	i = 0;
	k = 0;
	init_quotes(&quote);
	while (content[i])
	{
		if (is_operator(content[i], 0, &quote) > 0) //Modifier apres
			k++;
		i++;
	}
	return (k);
}


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

// int	get_operador_index(char *src, t_dlist **cmd_list)
// {
// 	int			i;
// 	int			op_count;
// 	int			tmp;
// 	t_quote		quote;
// 	t_operator	*operador_data;

// 	if (!src)
// 		return (1);
// 	op_count = count_operador(src);
// 	operador_data = malloc((op_count + 1) * sizeof(t_operator));
// 	if (!operador_data)
// 		return (1); // error
// 	operador_data[op_count] = (t_operator *) NULL;
// 	init_operador_var(&quote, &op_count, &i);

// 	while (src[i])
// 	{
// 		if (src[i] == '"' && quote.dbl_quote % 2 == 0)
// 			quote.dbl_quote++;
// 		if (src[i] == '\'' && quote.dbl_quote % 2 == 0)
// 			quote.dbl_quote++;
// 		tmp = is_operator(src, i, &quote);
// 		if(tmp > 0);
// 		{
// 			set_operator_info(src, i, &operador_data[op_count], &op_count);
// 			op_count++;
// 			i += tmp;
// 			continue ;
// 		}
// 		i++;
// 	}
// 	return (0);
// }

//fill the array on indexes of char that are operators in src
void	set_ope_char_i_arr(char *src, t_int_array *arr)
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
	i = 0;
}



//calculate the lenght of the array on indexes of char that are operators in src
void	set_ope_char_i_struc_arr(char *src, t_int_array *arr)
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
