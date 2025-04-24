/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 21:54:28 by ofilloux          #+#    #+#             */
/*   Updated: 2025/04/11 18:04:23 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	quote_increment(char *src, int i, t_quote *quote)
{
	if (src[i] == '"' && quote->sgl % 2 == 0)
		quote->dbl++;
	if (src[i] == '\'' && quote->dbl % 2 == 0)
		quote->sgl++;
}

void	init_quotes(t_quote *quote)
{
	quote->sgl = 0;
	quote->dbl = 0;
}

bool	all_quote_closed(char *s)
{
	int		i;
	bool	in_word;
	t_quote	quote;

	i = 0;
	in_word = false;
	init_quotes(&quote);
	while (s[i] != '\0')
	{
		if (s[i] == '\''&& quote.sgl % 2 == 1 && quote.dbl % 2 == 0)
			quote.sgl++;
		else if (s[i] == '\'' && quote.sgl % 2 == 0 && quote.dbl % 2 == 0 && !in_word)
			quote.sgl++;
		else if (s[i] == '"' && quote.sgl % 2 == 0 && quote.dbl  % 2 == 1)
			quote.dbl++;
		else if (s[i] == '"' && quote.sgl % 2 == 0 && quote.dbl  % 2 == 0 && !in_word)
			quote.dbl++;
		i++;
	}
	return (quote.sgl % 2 == 0 && quote.dbl % 2 == 0);
}

// cc ./utils/string/quotes.c ./utils/string/basics.c -g -o test
// int main()
// {
// 	char	**new_string;
// 	int		i = 0;

// 	if (all_quote_closed("hello"))
// 		printf("true\n");
// 	else
// 		printf("false\n");

// 	if (all_quote_closed("hell\"o"))
// 		printf("true\n");
// 	else
// 		printf("false\n");

// 	if (all_quote_closed("he\"l'l\"'o"))
// 		printf("true\n");
// 	else
// 		printf("false\n");
// 	return (0);
// }
