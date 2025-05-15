/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_quoted_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 09:50:17 by ofilloux          #+#    #+#             */
/*   Updated: 2025/05/15 09:51:54 by ofilloux         ###   ########.fr       */
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
