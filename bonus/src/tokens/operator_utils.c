/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 16:39:47 by ofilloux          #+#    #+#             */
/*   Updated: 2025/05/27 21:28:55 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

//return 0 if not operator, if operator return lenght
int	is_operator(char *src, int i, t_quote *quote)
{
	if (!quote)
		init_quotes(quote);
	if (quote->dbl_qt % 2 == 0 && quote->dbl_qt % 2 == 0)
	{
		if (src[i] == '>' && src[i + 1] && src[i + 1] == '>')
			return (2);
		else if (src[i] == '<' && src[i + 1] && src[i + 1] == '<')
			return (2);
		else if (src[i] == '<')
			return (1);
		else if (src[i] == '>')
			return (1);
	}
	return (0);
}

int	is_redirection(char *src, int i, t_quote *quote)
{
	if (quote->dbl_qt % 2 == 0 && quote->dbl_qt % 2 == 0)
	{
		if (src[i] == '>' && src[i + 1] && src[i + 1] == '>')
			return (2);
		else if (src[i] == '>')
			return (1);
	}
	return (0);
}

int	is_input_redir(char *src, int i, t_quote *quote)
{
	if (quote->dbl_qt % 2 == 0 && quote->dbl_qt % 2 == 0)
	{
		if (src[i] == '<' && src[i + 1] && src[i + 1] == '<')
			return (2);
		else if (src[i] == '<')
			return (1);
	}
	return (0);
}

void	init_operador_var(t_quote *quote, int *op_count, int *i)
{
	init_quotes(quote);
	*op_count = 0;
	*i = 0;
}
