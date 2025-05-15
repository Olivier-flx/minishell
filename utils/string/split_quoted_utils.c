/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_quoted_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 09:50:17 by ofilloux          #+#    #+#             */
/*   Updated: 2025/05/15 10:59:31 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void ignore_sep(char *s, int *i, char c, t_quote *qts)
{
	while (s[*i] == c && qts->dbl_quote % 2 == 0 && qts->sgl_quote % 2 == 0)
	{
		quote_increment(s, *i, qts);
		(*i)++;
	}
}

bool	should_break(char *s, int *i, char c, t_quote *qts)
{
	quote_increment(s, *i, qts);
	return (s[*i] == c && quote_are_closed(qts));
}

bool	should_skip_quote(char c, t_quote *qts, int *i)
{
	if ((c == '"'  && qts->sgl_quote % 2 == 0) \
		|| (c == '\'' && qts->dbl_quote % 2 == 0))
	{
		(*i)++;
		return (true);
	}
	return (false);
}
