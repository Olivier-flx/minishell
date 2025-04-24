/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 11:18:50 by ofilloux          #+#    #+#             */
/*   Updated: 2025/04/04 15:49:36 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

static int	ft_segment_count(const char *s, char c)
{
	int		i;
	int		count;
	bool	in_word;
	t_quote	quote;

	i = 0;
	count = 0;
	in_word = false;
	init_quotes(&quote);
	while (s[i] != '\0')
	{
		if (s[i] == '\''&& quote.sgl % 2 == 1 && quote.dbl % 2 == 0)
			quote.sgl++;
		else if (s[i] == '\'' && quote.sgl % 2 == 0 && quote.dbl % 2 == 0 && !in_word)
		{
			quote.sgl++;
			count++;
		}
		else if (s[i] == '"' && quote.sgl % 2 == 0 && quote.dbl  % 2 == 1)
			quote.dbl++;
		else if (s[i] == '"' && quote.sgl % 2 == 0 && quote.dbl  % 2 == 0 && !in_word)
		{
			quote.dbl++;
			count++;
		}
		else if (s[i] == c)
			in_word = false;
		else if (s[i] != c && quote.sgl % 2 == 0 && quote.dbl % 2 == 0 && !in_word)
		{
			count++;
			in_word = true;
		}
		i++;
	}
	return (count);
}

static int	ft_segment_len(int i, const char *s, char c)
{
	int		len;
	t_quote	quote;

	init_quotes(&quote);
	len = 0;
	while (s[i])
	{
		if (s[i] == '\'' && quote.sgl % 2 == 0 && quote.dbl % 2 == 0)
		{
			quote.sgl++;
			i++;
			continue ;
		}
		if (s[i] == '\'' && quote.sgl % 2 == 1 && quote.dbl % 2 == 0)
			break ;
		if (s[i] == '"' && quote.sgl % 2 == 0 && quote.dbl % 2 == 0)
		{
			quote.dbl++;
			i++;
			continue ;
		}
		if (s[i] == '"' && quote.sgl % 2 == 0 && quote.dbl % 2 == 0)
			break ;

		if (quote.sgl % 2 == 0 && quote.dbl % 2 == 0 && s[i] != c)
			len++;
		else if (quote.sgl % 2 == 1 && quote.dbl % 2 == 0 && s[i] != '\'')
			len++;
		else if (quote.sgl % 2 == 0 && quote.dbl % 2 == 1 && s[i] != '"')
			len++;
		else if (quote.sgl % 2 == 0 && quote.dbl % 2 == 0 && s[i] == c)
			break ;
		i++;
	}
	return (len + 1);
}

// // duplicate with char	**free_uncomplete_av(char **av, int i); in custom_frees.c
static char	**freeall(char **ns_ar, int i)
{
	i--;
	while (i >= 0)
	{
		free(ns_ar[i]);
		i--;
	}
	free(ns_ar);
	return (NULL);
}

static char	**ft_new_string_arr(char const *s, char c, char **ns_ar, int nb_segment)
{
	int		i;
	int		segment_i;
	int		s_i;
	t_quote	quote;

	init_quotes(&quote);
	i = 0;
	segment_i = 0;
	while (s[i] && segment_i < nb_segment)
	{
		s_i = 0;
		while (s[i] == c && quote.sgl % 2 == 0 && quote.dbl % 2 == 0)
			i++;
		ns_ar[segment_i] = malloc(ft_segment_len(i, s, c) * sizeof(char));
		if (ns_ar[segment_i] == NULL)
		{
			freeall(ns_ar, segment_i);
			return (NULL);
		}
		while (s[i] && (quote.sgl % 2 == 1 || quote.dbl % 2 == 1 || s[i] != c))
		{
			if (s[i] == '\'' && quote.dbl % 2 == 0)
				quote.sgl++;
			else if (s[i] == '"' && quote.sgl % 2 == 0)
				quote.dbl++;
			else
				ns_ar[segment_i][s_i++] = s[i];
			i++;
		}
		ns_ar[segment_i][s_i] = '\0';
		segment_i++;
	}
	ns_ar[segment_i] = 0;
	return (ns_ar);
}

char	**split_quoted(char const *s, char c)
{
	char	**ns_ar;
	int		segments_number;

	if (s == NULL)
		return (NULL);
	segments_number = ft_segment_count(s, c);
	ns_ar = malloc(((1 + segments_number)) * sizeof(char *));
	if (!ns_ar)
		return (0);
	ns_ar = ft_new_string_arr(s, c, ns_ar, segments_number);
	return (ns_ar);
}

// cc ./utils/string/ft_split.c ./utils/string/basics.c -g -o test
// int main()
// {
// 	char	**new_string;
// 	int		i = 0;

// 	// new_string = split_quoted("he'l'lo > \"le '  ' fcdf  \"    Yo", ' ');
// 	//new_string = split_quoted("he\"l\"lo > \"le '  ' fcdf  \"    Yo", ' ');
// 	new_string = split_quoted(" h\"e'l'o  !\" ces\"T\" > le 'nouv\"e a u\"    monde !'  | ce'st' s\"ur\"", ' ');
// 	//new_string = split_quoted("hello > 'le fcdf monde'    | cest'   ' pas moi      moi", ' ');
// 	while (new_string[i])
// 	{
// 		printf("%i] : `%s`\n", i ,new_string[i]);
// 		free(new_string[i]);
// 		i++;
// 	}
// 	free(new_string);
// 	return (0);
// }
