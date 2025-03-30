/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_set_of_char.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 11:18:50 by ofilloux          #+#    #+#             */
/*   Updated: 2025/03/30 18:52:03 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

static int	ft_segment_count(char *s, t_int_array *sep_indexes)
{
	int		i;
	int		count;
	bool	in_segment;
	t_quote	quote;

	i = 0;
	count = 0;
	in_segment = false;
	init_quotes(&quote);
	while (s[i] != '\0')
	{
		quote_increment(s, i, &quote);
		if (is_seperator(s, i, &quote) > 0 && s[i] == ' ')// @optimize // si space separator to ignore
			in_segment = false;
		else if (is_seperator(s, i, &quote) > 0 && s[i] != ' ') // si operateur mais pas espace
		{
			count++;
			printf("segment incremented at s[%i] = %c\n", i, s[i]); // @debug
			i += is_seperator(s, i, &quote);
			in_segment = false;
			continue;
		}
		else if (is_seperator(s, i, &quote) == 0 && !in_segment) // si ce n'est pas un operateur
		{
			count++;
			printf("segment incremented at s[%i] = %c\n", i, s[i]); // @debug
			in_segment = true;
		}
		i++;
	}
	return (count);
}

static int	ft_segment_len(int i, char *s, t_quote *quote, t_int_array *separators)
{
	int		len;
	int 	flag;

	len = 0;
	flag = 0;
	if (is_seperator(s, i, quote) > 0 && s[i]!= ' ')
		return(is_seperator(s, i, quote));
	if (is_seperator(s, i, quote) > 0 && s[i] == ' ')
		return (0);
	while (s[i] && !int_var_in_arr(i, separators))
	{
		len++;
		i++;
	}
	return (len);
}

static char	**ft_new_string_arr(char *s, char **ns_ar, int nb_segment, t_int_array *separators)
{
	int		i;
	int		segment_i;
	int		s_i;
	t_quote	quote;
	int		seg_len;
	int		debug = 0; //@debug
	int		flag = 0;

	init_quotes(&quote);
	i = 0;
	segment_i = 0;
	seg_len = 0;
	while (s[i] && segment_i < nb_segment)
	{
		s_i = 0;
		while (is_seperator(s, i, &quote) > 0 && s[i] == ' ') // if space not in quote, ignore
			i++;

		seg_len = ft_segment_len(i, s, &quote, separators);
		printf("segment len = %i\n", seg_len); // @debug

		ns_ar[segment_i] = malloc(sizeof(char) * (seg_len + 1));
		if (ns_ar[segment_i] == NULL)
		{
			free_uncomplete_av(ns_ar, segment_i);
			return (NULL);
		}

		/// DEBUG ce while est la source du probleme !!
		while (s[i])
		{
			if (s[i] == '\'' && quote.dbl % 2 == 0)
				quote.sgl++;
			if (s[i] == '"' && quote.sgl % 2 == 0)
				quote.dbl++;
			flag = is_seperator(s, i, &quote);
			if(flag > 0)
			{
				while (s_i < flag)
					ns_ar[segment_i][s_i++] = s[i++];
				break;
			}
			else
				ns_ar[segment_i][s_i++] = s[i++];
		}
		printf("ft_new_string_arr[%i] = `%s`\n", segment_i,ns_ar[segment_i]); // @debug
		ns_ar[segment_i][s_i] = '\0';
		segment_i++;
	}
	ns_ar[segment_i] = 0;
	return (ns_ar);
}

static void	init_var_ft_new_string_arr(int *i, int *segment_i, int *flag)
{
	*i = 0;
	*segment_i = 0;
	*flag = 0;
}

create_token(char *s, int *i, t_quote *quote)
{
	int flag;

	flag = 0;
}


static char	**ft_new_string_arr2(char *s, char **ns_ar, int nb_segment, t_int_array *separators)
{
	int		i;
	int		segment_i;
	int		s_i;
	t_quote	quote;
	int		flag;

	init_quotes(&quote);
	init_var_ft_new_string_arr(&i, &segment_i, &flag);
	while (s[i] && segment_i < nb_segment)
	{
		s_i = 0;
		while (is_seperator(s, i, &quote) > 0 && s[i] == ' ') // if space not in quote, ignore
			i++;
		ns_ar[segment_i] = malloc(sizeof(char) * (ft_segment_len(i, s, &quote, separators) + 1));
		if (NULL == ns_ar[segment_i])
			return (free_uncomplete_av(ns_ar, segment_i), NULL);
		while (s[i])
		{
			quote_increment(s, i, &quote);
			flag = is_seperator(s, i, &quote);
			if(flag > 0)
			{
				while (s_i < flag)
					ns_ar[segment_i][s_i++] = s[i++];
				break;
			}
			else
				ns_ar[segment_i][s_i++] = s[i++];
		}
		ns_ar[segment_i][s_i] = '\0';
		segment_i++;
	}
	ns_ar[segment_i] = 0;
	return (ns_ar);
}

char	**split_quoted2(char *s,t_data *data)
{
	char	**ns_ar;
	int		segments_number;

	ns_ar = NULL;
	if (s == NULL)
		return (NULL);
	set_separator_char_i_struc_arr(s, &(data->token_separators_char_i));
	segments_number = ft_segment_count(s, &(data->token_separators_char_i));
	printf("segments_number = %i\n", segments_number); // @debug
	ns_ar = malloc(((1 + segments_number)) * sizeof(char *));
	if (!ns_ar)
		return (0);
	ns_ar = ft_new_string_arr2(s, ns_ar, segments_number, &(data->token_separators_char_i));
	return (ns_ar);
}

// cc ./utils/string/ft_split_set_of_char.c ./src/tokens/operador.c ./utils/string/basics.c ./utils/string/quotes.c -g -o test

//cc -g -O0 -o test ./utils/string/ft_split_set_of_char.c ./utils/string/basics.c ./src/tokens/token_separators.c ./src/tokens/operator.c ./utils/string/quotes.c ./utils/arrays/methods.c ./utils/arrays/arr_frees.c
int main()
{
	char	**new_string;
	int		i = 0;
	t_data	data;

	new_string = split_quoted2("hel>lo >> \"cest\" o'  Y''e'", &data);
	//new_string = split_quoted("he'l'lo > \"le '  ' fcdf  \"    Yo", ' ');
	//new_string = split_quoted("he\"l\"lo > \"le '  ' fcdf  \"    Yo", ' ');
	//new_string = split_quoted2(" h\"e\">>'l<'>o  !\" ces\"T\" > l>e 'nouv\"e a u\"    monde !'  | ce'st' s\"ur\"");
	//new_string = split_quoted("hello > 'le fcdf monde'    | cest'   ' pas moi      moi", ' ');
	printf("----------array operators ------------ \n");
	fflush(stdout); // @debug
	print_int_arr(&(data.token_separators_char_i));
	while (new_string && new_string[i])
	{
		//printf("segment [%i] : `%s`\n", i ,new_string[i]);
		free(new_string[i]);
		i++;
	}
	if (new_string)
		free(new_string);
	return (0);
}
