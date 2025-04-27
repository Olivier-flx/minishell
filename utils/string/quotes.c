/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 21:54:28 by ofilloux          #+#    #+#             */
/*   Updated: 2025/04/27 09:15:00 by ofilloux         ###   ########.fr       */
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

/**
 * tocken_quote_closed - Checks if all quotes in a given string are properly closed.
 * @s: The input string to check.
 *
 * This function analyzes a string to determine whether all single (') and double (") quotes
 * are correctly closed. It tracks the state of single and double quotes separately,
 * ensuring that quotes are only considered opened or closed when not inside another quote.
 *
 * The function uses a t_quote structure to count quote occurrences and returns true
 * if all quotes are balanced (i.e., closed), or false if any quote remains open.
 *
 * Returns:
 *   true if all quotes are closed,
 *   false if any quote is left open.
 */
bool	tocken_quote_closed(char *s)
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

/**
 * quote_are_closed - Checks if all quotes are properly closed.
 * @quote: Pointer to the quote tracking structure.
 *
 * This function returns true if both single and double quotes are closed,
 * otherwise returns false.
 *
 * Returns:
 *   true if all quotes are closed,
 *   false if any quote remains open.
 */
bool	quote_are_closed(t_quote *quote)
{
	return (quote->sgl % 2 == 0 && quote->dbl % 2 == 0);
}

// cc ./utils/string/quotes.c ./utils/string/basics.c -g -o test
// int main()
// {
// 	char	**new_string;
// 	int		i = 0;

// 	if (tocken_quote_closed("hello"))
// 		printf("true\n");
// 	else
// 		printf("false\n");

// 	if (tocken_quote_closed("hell\"o"))
// 		printf("true\n");
// 	else
// 		printf("false\n");

// 	if (tocken_quote_closed("he\"l'l\"'o"))
// 		printf("true\n");
// 	else
// 		printf("false\n");
// 	return (0);
// }
