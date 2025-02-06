/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 11:18:50 by ofilloux          #+#    #+#             */
/*   Updated: 2025/01/25 11:41:24 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

static int	ft_segment_count(const char *s, char c)
{
	int		i;
	int		count;
	bool	in_word;
	bool	in_quotes;

	i = 0;
	count = 0;
	in_word = false;
	in_quotes = false;
	while (s[i] != '\0')
	{
		if (s[i] == '\'' && in_quotes)
			in_quotes = false;
		else if (s[i] == '\'' && !in_quotes)
		{
			in_quotes = true;
			count++;
		}
		else if (s[i] == c)
			in_word = false;
		else if (s[i] != c && !in_quotes && !in_word)
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
	int	len;
	bool	in_quote;

	len = 0;
	in_quote = false;
	while (s[i])
	{
		if (s[i] == '\'' && !in_quote)
		{
			in_quote = true;
			i++;
			continue;
		}
		if (s[i] == '\'' && in_quote)
			break;

		if (!in_quote && s[i] != c)
			len++;
		else if (in_quote && s[i] != '\'')
			len++;
		else if (!in_quote && s[i] == c)
			break;
		i++;
	}
	return (len + 1);
}

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
	int	i;
	int	segment_i;
	int	s_i;
	bool in_quote;

	i = 0;
	segment_i = 0;
	in_quote = false;
	while (s[i] && segment_i < nb_segment)
	{
		s_i = 0;
		while (s[i] == c && !in_quote)
			i++;
		ns_ar[segment_i] = malloc(ft_segment_len(i, s, c) * sizeof(char));
		if (ns_ar[segment_i] == NULL)
		{
			freeall(ns_ar, segment_i);
			return (NULL);
		}
		while (s[i] && (in_quote || s[i] != c))
		{
			if (s[i] == '\'' && !in_quote)
				in_quote = true;
			else if (s[i] == '\'' && in_quote)
				in_quote = false;
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

char	**split_to_list(char const *s, char c)
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
