/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 11:58:34 by ofilloux          #+#    #+#             */
/*   Updated: 2025/06/04 11:54:24 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

bool	is_quote(char c)
{
	return (c == '\'' || c == '"');
}

bool	bool_quote_increment(char *src, int *i, t_quote *qts, bool i_inc)
{
	bool	flag;

	flag = false;
	if (src[*i] == '"' && qts->sgl_qt % 2 == 0 && qts->acc % 2 == 0)
	{
		flag = true;
		qts->dbl_qt++;
	}
	if (src[*i] == '\'' && qts->dbl_qt % 2 == 0 && qts->acc % 2 == 0)
	{
		flag = true;
		qts->sgl_qt++;
	}
	if (flag && i_inc)
		(*i)++;
	return (flag);
}
