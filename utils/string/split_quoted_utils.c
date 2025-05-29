/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_quoted_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 09:50:17 by ofilloux          #+#    #+#             */
/*   Updated: 2025/05/29 10:09:22 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void ignore_sep(char *s, int *i, char c, t_quote *qts)
{
	while (s[*i] == c && qts->dbl_qt % 2 == 0 && qts->sgl_qt % 2 == 0)
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

bool qts_en_seguida_ignore(char *s, int i,t_quote *qts)
{
	return((qts->dbl_qt % 2 == 1 || qts->sgl_qt % 2 == 1) && \
			((s[i] == '\'' && s[i + 1] == '\'') \
			|| (s[i] == '"' && s[i + 1] == '"')));
}

bool	should_skip_quote(char *s, char c, t_quote *qts, int *i)
{
	if(qts_en_seguida_ignore(s, *i, qts)) //@test id 3
	{
		(*i)++;
		quote_increment(s, *i, qts);
		(*i)++;
		return (true);
	}
	else if ((c == '"'  && qts->sgl_qt % 2 == 0) \
		|| (c == '\'' && qts->dbl_qt % 2 == 0))
	{
		(*i)++;
		return (true);
	}
	return (false);
}
