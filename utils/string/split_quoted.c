/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_quoted.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 11:18:50 by ofilloux          #+#    #+#             */
/*   Updated: 2025/06/02 12:14:38 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

//V1
// static int	ft_count_segment(char *s, char c)
// {
// 	int		i;
// 	int		count;
// 	bool	in_word;
// 	t_quote	quote;

// 	i = 0;
// 	count = 0;
// 	in_word = false;
// 	init_quotes(&quote);
// 	while (s[i] != '\0')
// 	{
// 		quote_increment(s, i, &quote);
// 		if (s[i] == c &&  quote_are_closed(&quote))
// 			in_word = false;
// 		else if (s[i] != c && !in_word)
// 		{
// 			count++;
// 			in_word = true;
// 		}
// 		i++;
// 	}
// 	return (count);
// }


static int	ft_count_segment(char *s, char c)
{
	int		i;
	int		count;
	bool	in_word;
	t_quote	qts;

	i = 0;
	count = 0;
	in_word = false;
	init_quotes(&qts);
	while (s[i] != '\0')
	{
		quote_increment(s, i, &qts);
		if (qts_en_seguida_ignore(s, i, &qts)) // @test id 3
			i++;
		else if (s[i] == c &&  quote_are_closed(&qts))
			in_word = false;
		else if (s[i] != c && !in_word)
		{
			count++;
			in_word = true;
		}
		i++;
	}
	//printf("ft_count_segment -> count = %i\n", count); // @debug
	return (count);
}

static int no_qts_seg_len(int i, char *s, char sep, t_quote *qts)
{
	int		len;
	t_quote	q_cpy;

	len = 0;
	q_cpy = *qts;
	while (s[i])
	{
		quote_increment(s, i, &q_cpy);
		if (s[i] == sep && quote_are_closed(&q_cpy))
			break;
		if (should_skip_quote(s, s[i], &q_cpy, &i))
			continue;
		len++;
		i++;
	}
	return (len);
}
// static int no_qts_seg_len(int i, char *s, char sep, t_quote *qts)
// {
// 	int		len;

// 	len = 0;
// 	while (s[i])
// 	{
// 		quote_increment(s, i, qts);
// 		if (s[i] == sep && quote_are_closed(qts))
// 			break;
// 		if ((s[i] == '"' && qts->sgl_qt % 2 == 0)
// 			|| (s[i] == '\'' && qts->dbl_qt % 2 == 0))
// 		{
// 			i++;
// 			continue;
// 		}
// 		len++;
// 		i++;
// 	}
// 	return (len + 1);
// }



char	*process_segment(char *s, int *i, char c, t_quote *qts)
{
	int		s_i;
	char	*new_seg;

	s_i = 0;
	ignore_unecesary_char(s, i, c, qts);
	if (!s[*i])
		return (NULL);
	new_seg = malloc((no_qts_seg_len(*i, s, c, qts) + 1) * sizeof(char));
	if (new_seg == NULL)
		return (NULL);
	printf ("no_qts_seg_len(*i, s, c, qts) = %i\n", no_qts_seg_len(*i, s, c, qts)); //@debug
	while (s[*i])
	{
		if (should_break(s, i, c, qts))
			break;
		if (should_skip_quote(s, s[*i], qts, i))
			continue;
		new_seg[s_i++] = s[(*i)++];
	}
	new_seg[s_i] = '\0';
	printf("process_segment new_seg = `%s`\n", new_seg); // @debug
	return (new_seg);
}

static char	**ft_new_string_arr(char *s, char c, char **ns_ar, int nb_segment)
{
	int		i;
	int		segment_i;
	t_quote	qts;

	init_quotes(&qts);
	i = 0;
	segment_i = 0;
	while (s[i] && segment_i < nb_segment)
	{
		ns_ar[segment_i] = process_segment(s, &i, c, &qts);
		if (ns_ar[segment_i] == NULL)
			return (free_uncomplete_av(&ns_ar, segment_i));
		segment_i++;
	}
	ns_ar[segment_i] = 0;
	return (ns_ar);
}

char	**split_quoted(char *s, char c)
{
	char	**ns_ar;
	int		segments_number;

	if (!s)
		return (NULL);
	segments_number = ft_count_segment(s, c);
	ns_ar = malloc(((1 + segments_number)) * sizeof(char *));
	if (!ns_ar)
		return (0);
	ns_ar = ft_new_string_arr(s, c, ns_ar, segments_number);
	return (ns_ar);
}

/* static void	init_var_ft_new_str_arr(int *i, int *segment_i)
{
	*i = 0;
	*segment_i = 0;
}

static char *allocate_next_segment(char *s, int i, \
									t_quote *quote, t_int_array *separators)
{
	int		len;
	char	*segment;

	len = ft_segment_len(i, s, quote, separators);
	segment = malloc(sizeof(char) * (len + 1));
	return (segment);
}

static int fill_token_segment(char *s, char *dest, int *i, t_quote *quote)
{
	int	s_i;
	int	flag;

	s_i = 0;
	flag = 0;
	while (s[*i])
	{
		quote_increment(s, *i, quote);
		flag = is_seperator(s, *i, quote);
		if (flag > 0)
		{
			while (s_i < flag)
				dest[s_i++] = s[(*i)++];
			break;
		}
		else
			dest[s_i++] = s[(*i)++];
	}
	dest[s_i] = '\0';
	return (s_i);
}

static char	**ft_new_str_arr(char *s, char **ns_ar, int nb_segment, t_int_array *separators)
{
	int		i;
	int		segment_i;
	t_quote	quote;

	init_quotes(&quote);
	init_var_ft_new_str_arr(&i, &segment_i);
	while (s[i] && segment_i < nb_segment)
	{
		while (is_seperator(s, i, &quote) > 0 && ft_isspace(s[i]))
			i++;
		ns_ar[segment_i] = allocate_next_segment(s, i, &quote, separators);
		if (!ns_ar[segment_i])
			return (free_uncomplete_av(ns_ar, segment_i), NULL);
		fill_token_segment(s, ns_ar[segment_i], &i, &quote);
		segment_i++;
	}
	ns_ar[segment_i] = 0;
	return (ns_ar);
}

char	**split_quoted(char *s, t_data *data)
{
	char	**ns_ar;
	int		tokens_number;
	t_quote	quote;

	init_quotes(&quote);
	ns_ar = NULL;
	if (s == NULL)
		return (NULL);
	set_separator_char_i_struc_arr(s, &(data->token_separators_char_i));
	tokens_number = ft_segment_count(s, 0, 0, &quote);
	ns_ar = malloc(((1 + tokens_number)) * sizeof(char *));
	if (!ns_ar)
		return (0);
	ns_ar = ft_new_str_arr(s, ns_ar, tokens_number, &(data->token_separators_char_i));
	ft_free((void **) &(data->token_separators_char_i));
	return (ns_ar);
} */

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
