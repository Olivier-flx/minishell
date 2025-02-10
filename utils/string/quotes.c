/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 21:54:28 by ofilloux          #+#    #+#             */
/*   Updated: 2025/02/10 21:59:14 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	increment_quotes(char *src, int i, t_quote *quote)
{
	if (src[i] == '"' && (quote->sgl) % 2 == 0)
		(quote->dbl)++;
	if (src[i] == '\'' && (quote->dbl) % 2 == 0)
		(quote->sgl)++;
}
