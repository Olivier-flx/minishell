/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_sgmt_count.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 14:12:14 by ofilloux          #+#    #+#             */
/*   Updated: 2025/06/04 12:08:05 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	quote_accolade_increment(char *src, int i, t_quote *quote)
{
	if (src[i] == '"' && quote->sgl_qt % 2 == 0 && quote->acc % 2 == 0)
		quote->dbl_qt++;
	else if (src[i] == '\'' && quote->dbl_qt % 2 == 0 && quote->acc % 2 == 0)
		quote->sgl_qt++;
	else if (src[i] == '{' && i > 0 && src[i - 1] == '$'
		&& qts_acc_closed(quote))
		quote->acc++;
	else if (src[i] == '}' && quote->acc % 2 == 1 && quote->sgl_qt % 2 == 0 \
				&& quote->dbl_qt % 2 == 0)
		quote->acc++;
}

static void	process_word(int *i, int *count, bool *in_segment)
{
	if (!*in_segment)
	{
		(*count)++;
		*in_segment = true;
	}
	(*i)++;
}

static int	operator_len(char *s, int i, t_quote *quote)
{
	if (!qts_acc_closed(quote))
		return (0);
	if (s[i] == '>' && s[i + 1] == '>')
		return (2);
	if (s[i] == '<' && s[i + 1] == '<')
		return (2);
	if (s[i] == '>' || s[i] == '<' || s[i] == '|')
		return (1);
	return (0);
}

int	ft_segment_count(char *s, int i, int count, t_quote *quote)
{
	bool	in_segment;
	int		len;

	in_segment = false;
	while (s && s[i])
	{
		quote_accolade_increment(s, i, quote);
		len = operator_len(s, i, quote);
		if (len > 0)
		{
			count++;
			in_segment = false;
			i += len;
			continue ;
		}
		if (ft_isspace((unsigned char)s[i]))
		{
			in_segment = false;
			i++;
			continue ;
		}
		process_word(&i, &count, &in_segment);
	}
	return (count);
}

int	ft_segment_len(int i, char *s, t_quote *quote, t_int_array *separators)
{
	int		len;

	len = 0;
	if (is_seperator(s, i, quote) > 0 && !ft_isspace(s[i]))
		return (is_seperator(s, i, quote));
	if (is_seperator(s, i, quote) > 0 && ft_isspace(s[i]))
		return (0);
	while (s[i] && !int_var_in_arr(i, separators))
	{
		len++;
		i++;
	}
	return (len);
}
