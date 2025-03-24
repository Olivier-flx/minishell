/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_set_of_char.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 11:18:50 by ofilloux          #+#    #+#             */
/*   Updated: 2025/03/24 18:04:32 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

// int	substr_is_delimiter(char *s, char **deli, int i)
// {
// 	int	j;

// 	j = 0;
// 	while (deli[j] && deli[j][0])
// 	{
// 		if (s[i] && s[i + 1] && ft_strncmp(deli[j],s + i, s_len(deli[j])) == 0)
// 			return (1);
// 		else if (s[i] && !s[i + 1] && ft_strncmp(deli[j],s + i, s_len(deli[j])) == 0)
// 		{
// 			return (1);
// 		}
// 		j++;
// 	}
// 	return(0);
// }

// @info : return the len of the delimiter OR 0 if not a delimiter
int	is_operator_or_space(char *src, int i, t_quote *quote)
{
	if (quote->sgl % 2 == 0  && quote->dbl % 2 == 0)
	{
		if (src[i] == '>' && src[i + 1] && src[i + 1] == '>')
			return(2);
		else if (src[i] == '<' && src[i + 1] && src[i + 1] == '<')
			return(2);
		else if (src[i] == 124)
			return(1);
		else if (src[i] == '<')
			return(1);
		else if (src[i] == '>')
			return(1);
		else if (src[i] == ' ')
			return(1);
	}
	return (0);
}


int	simple_quote_increment_segment_count(char *s, int *i, t_quote *quote, bool in_word)
{
	int	count;

	count = 0;
	if (s[*i] == '\''&& quote->sgl % 2 == 1 && quote->dbl % 2 == 0)
		{
			quote->sgl++;
			*i++;
		}
	else if (s[*i] == '\'' && quote->sgl % 2 == 0 && quote->dbl % 2 == 0 && !in_word)
	{
		quote->sgl++;
		count++;
	}
	else if (s[*i] == '"' && quote->sgl % 2 == 0 && quote->dbl  % 2 == 1)
	{
		quote->dbl++;
		*i++;
	}
	else if (s[*i] == '"' && quote->sgl % 2 == 0 && quote->dbl  % 2 == 0 && !in_word)
	{
		quote->dbl++;
		count++;
	}
	if (count > 0)
		*i++;
	return (count);
}

static int	ft_segment_count(char *s)
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
		count += simple_quote_increment_segment_count(s, &i, &quote, in_word);

		/////// @legacy //////
		// if (s[i] == '\''&& quote.sgl % 2 == 1 && quote.dbl % 2 == 0)
		// 	quote.sgl++;
		// else if (s[i] == '\'' && quote.sgl % 2 == 0 && quote.dbl % 2 == 0 && !in_word)
		// {
		// 	quote.sgl++;
		// 	count++;
		// }
		// else if (s[i] == '"' && quote.sgl % 2 == 0 && quote.dbl  % 2 == 1)
		// 	quote.dbl++;
		// else if (s[i] == '"' && quote.sgl % 2 == 0 && quote.dbl  % 2 == 0 && !in_word)
		// {
		// 	quote.dbl++;
		// 	count++;
		// }
		///////////////////////
		if (is_operator_or_space(s, i, &quote) > 0 && s[i] == ' ')// @optimize
			in_word = false;
		else if (is_operator_or_space(s, i, &quote) > 0 && s[i] != ' ') // NF
		{
			count++;
			in_word = false;
			i += is_operator_or_space(s, i, &quote);
			continue;
		}
		else if (is_operator_or_space(s, i, &quote) == 0 && quote.sgl % 2 == 0 && quote.dbl % 2 == 0 && !in_word)
		{
			count++;
			in_word = true;
			i++;
			continue;
		}
		i++;
	}
	return (count);
}


// static int	ft_segment_count(const char *s, char c)
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
// 		if (s[i] == '\''&& quote.sgl % 2 == 1 && quote.dbl % 2 == 0)
// 			quote.sgl++;
// 		else if (s[i] == '\'' && quote.sgl % 2 == 0 && quote.dbl % 2 == 0 && !in_word)
// 		{
// 			quote.sgl++;
// 			count++;
// 		}
// 		else if (s[i] == '"' && quote.sgl % 2 == 0 && quote.dbl  % 2 == 1)
// 			quote.dbl++;
// 		else if (s[i] == '"' && quote.sgl % 2 == 0 && quote.dbl  % 2 == 0 && !in_word)
// 		{
// 			quote.dbl++;
// 			count++;
// 		}
// 		else if (s[i] == c)
// 			in_word = false;
// 		else if (s[i] != c && quote.sgl % 2 == 0 && quote.dbl % 2 == 0 && !in_word)
// 		{
// 			count++;
// 			in_word = true;
// 		}
// 		i++;
// 	}
// 	return (count);
// }

//@info - if return 0 --> continue ; if return 1 --> break.
int	quote_incrementation_len(char *s, int *i, t_quote *quote, int *len)
{
	if (s[*i] == '\'' && quote->sgl % 2 == 0 && quote->dbl % 2 == 0)
	{
		quote->sgl++;
		*i++;
		*len ++; // @NF
		return (0);
	}
	if (s[*i] == '\'' && quote->sgl % 2 == 1 && quote->dbl % 2 == 0)
	{
		*len++;// @NF
		return (1);
	}
	if (s[*i] == '"' && quote->sgl % 2 == 0 && quote->dbl % 2 == 0)
	{
		quote->dbl++;
		*i++;
		*len ++; // @NF
		return (0);
	}
	if (s[*i] == '"' && quote->sgl % 2 == 0 && quote->dbl % 2 == 1)
	{
		*len++; // @NF
		return (1);
	}
	return (-1);
}

static int	ft_segment_len(int i, char *s)
{
	int		len;
	t_quote	quote;
	int 	flag;

	init_quotes(&quote);
	len = 0;
	flag = 0;
	if (is_operator_or_space(s, i, &quote) > 0 && s[i]!= ' ')
		return(is_operator_or_space(s, i, &quote));
	while (s[i])
	{
		flag = quote_incrementation_len(s, &i, &quote, &len);
		if (flag == 0)
			continue ;
		else if (flag == 1)
			break ;
		///////// Quote incrementation /////////// @legacy
			// if (s[i] == '\'' && quote.sgl % 2 == 0 && quote.dbl % 2 == 0)
			// {
			// 	quote.sgl++;
			// 	i++;
			// 	len ++; // @NF
			// 	continue ;
			// }
			// if (s[i] == '\'' && quote.sgl % 2 == 1 && quote.dbl % 2 == 0)
			// {
			// 	len++;// @NF
			// 	break ;
			// }
			// if (s[i] == '"' && quote.sgl % 2 == 0 && quote.dbl % 2 == 0)
			// {
			// 	quote.dbl++;
			// 	i++;
			// 	len ++; // @NF
			// 	continue ;
			// }
			// if (s[i] == '"' && quote.sgl % 2 == 0 && quote.dbl % 2 == 1)
			// {
			// 	len ++; // @NF
			// 	break ;
			// }
		///////////////////////

		// @info : if not an delim and all quotes are closed, the len++
		if (quote.sgl % 2 == 0 && quote.dbl % 2 == 0 && is_operator_or_space(s, i, &quote) == 0)
			len++;
		// @Util : if we take in account quotes in the segment len, it seem useless
			// else if (quote.sgl % 2 == 1 && quote.dbl % 2 == 0 && s[i] != '\'')
			// 	len++;
			// else if (quote.sgl % 2 == 0 && quote.dbl % 2 == 1 && s[i] != '"')
			// 	len++;
// Probleme, si le segment est lui meme un operateur.
		// else if (quote.sgl % 2 == 0 && quote.dbl % 2 == 0 && is_operator_or_space(s, i, &quote) > 0 && s[i] != ' ')
		// {
		// 	len += is_operator_or_space(s, i, &quote); // @optimize
		// 	i += is_operator_or_space(s, i, &quote); // @optimize
		// 	continue;
		// }
		else if (quote.sgl % 2 == 0 && quote.dbl % 2 == 0 && is_operator_or_space(s, i, &quote) > 0 /*&& s[i] == ' '*/)
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

static char	**ft_new_string_arr(char *s, char **ns_ar, int nb_segment)
{
	int		i;
	int		segment_i;
	int		s_i;
	t_quote	quote;
	int		debug = 0; //@debug

	init_quotes(&quote);
	i = 0;
	segment_i = 0;
	while (s[i] && segment_i < nb_segment)
	{
		s_i = 0;
		while (is_operator_or_space(s, i, &quote) > 0 && s[i] == ' ' && quote.sgl % 2 == 0 && quote.dbl % 2 == 0)
			i++;
		debug
		printf("segment len = %i\n", ft_segment_len(i, s) - 1); // @debug
		ns_ar[segment_i] = malloc(ft_segment_len(i, s) * sizeof(char));
		if (ns_ar[segment_i] == NULL)
		{
			freeall(ns_ar, segment_i);
			return (NULL);
		}
		while (s[i] && (quote.sgl % 2 == 1 || quote.dbl % 2 == 1 || (is_operator_or_space(s, i, &quote) >= 0 && s[i] != ' ')))
		{
			if (s[i] == '\'' && quote.dbl % 2 == 0)
				quote.sgl++;
			if (s[i] == '"' && quote.sgl % 2 == 0)
				quote.dbl++;
			ns_ar[segment_i][s_i++] = s[i];
			i++;
		}
		ns_ar[segment_i][s_i] = '\0';
		segment_i++;
	}
	ns_ar[segment_i] = 0;
	return (ns_ar);
}


// static char	**ft_new_string_arr(char *s, char **ns_ar, int nb_segment)
// {
// 	int		i;
// 	int		segment_i;
// 	int		s_i;
// 	t_quote	quote;

// 	init_quotes(&quote);
// 	i = 0;
// 	segment_i = 0;
// 	while (s[i] && segment_i < nb_segment)
// 	{
// 		s_i = 0;
// 		while (is_operator_or_space(s, i, &quote) > 0 && quote.sgl % 2 == 0 && quote.dbl % 2 == 0)
// 			i++;
// 		ns_ar[segment_i] = malloc(ft_segment_len(i, s) * sizeof(char));
// 		if (ns_ar[segment_i] == NULL)
// 		{
// 			freeall(ns_ar, segment_i);
// 			return (NULL);
// 		}
// 		while (s[i] && (quote.sgl % 2 == 1 || quote.dbl % 2 == 1 || is_operator_or_space(s, i, &quote) == 0))
// 		{
// 			if (s[i] == '\'' && quote.dbl % 2 == 0)
// 				quote.sgl++;
// 			else if (s[i] == '"' && quote.sgl % 2 == 0)
// 				quote.dbl++;
// 			else
// 				ns_ar[segment_i][s_i++] = s[i];
// 			i++;
// 		}
// 		ns_ar[segment_i][s_i] = '\0';
// 		segment_i++;
// 	}
// 	ns_ar[segment_i] = 0;
// 	return (ns_ar);
// }

char	**split_quoted2(char *s)
{
	char	**ns_ar;
	int		segments_number;

	ns_ar = NULL;
	if (s == NULL)
		return (NULL);
	segments_number = ft_segment_count(s);
	printf("segments_number = %i\n", segments_number); // @debug
	ns_ar = malloc(((1 + segments_number)) * sizeof(char *));
	if (!ns_ar)
		return (0);
	ns_ar = ft_new_string_arr(s, ns_ar, segments_number);
	return (ns_ar);
}

// cc ./utils/string/ft_split_set_of_char.c ./utils/string/basics.c ./utils/string/quotes.c -g -o test
int main()
{
	char	**new_string;
	int		i = 0;

	new_string = split_quoted2("hel>lo >> Y'o'");
	// new_string = split_quoted("he'l'lo > \"le '  ' fcdf  \"    Yo", ' ');
	//new_string = split_quoted("he\"l\"lo > \"le '  ' fcdf  \"    Yo", ' ');
	//new_string = split_quoted2(" h\"e\">>'l<'>o  !\" ces\"T\" > l>e 'nouv\"e a u\"    monde !'  | ce'st' s\"ur\"");
	//new_string = split_quoted("hello > 'le fcdf monde'    | cest'   ' pas moi      moi", ' ');
	while (new_string && new_string[i])
	{
		printf("segment [%i] : `%s`\n", i ,new_string[i]);
		free(new_string[i]);
		i++;
	}
	if (new_string)
		free(new_string);
	return (0);
}
