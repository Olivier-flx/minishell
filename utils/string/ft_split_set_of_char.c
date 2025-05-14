/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_set_of_char.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 11:18:50 by ofilloux          #+#    #+#             */
/*   Updated: 2025/05/14 23:47:14 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

static void	init_var_ft_new_str_arr(int *i, int *segment_i)
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
			return (free_uncomplete_av(&ns_ar, segment_i), NULL);
		fill_token_segment(s, ns_ar[segment_i], &i, &quote);
		segment_i++;
	}
	ns_ar[segment_i] = 0;
	return (ns_ar);
}

char	**split_quoted2(char *s, t_data *data)
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
}

// cc ./utils/string/ft_split_set_of_char.c ./src/tokens/operador.c ./utils/string/basics.c ./utils/string/quotes.c -g -o test

//cc -g -O0 -o test ./utils/string/ft_split_set_of_char.c ./utils/string/basics.c ./src/tokens/token_separators.c ./src/tokens/operator.c ./utils/string/quotes.c ./utils/arrays/methods.c ./utils/arrays/arr_frees.c
// int main()
// {
// 	char	**new_string;
// 	int		i = 0;
// 	t_data	data;

// 	new_string = split_quoted2("hel>lo >> \"cest\" o'  Y''e'", &data);
// 	//new_string = split_quoted("he'l'lo > \"le '  ' fcdf  \"    Yo", ' ');
// 	//new_string = split_quoted("he\"l\"lo > \"le '  ' fcdf  \"    Yo", ' ');
// 	//new_string = split_quoted2(" h\"e\">>'l<'>o  !\" ces\"T\" > l>e 'nouv\"e a u\"    monde !'  | ce'st' s\"ur\"");
// 	//new_string = split_quoted("hello > 'le fcdf monde'    | cest'   ' pas moi      moi", ' ');
// 	printf("----------array operators ------------ \n");
// 	fflush(stdout); // @debug
// 	print_int_arr(&(data.token_separators_char_i));
// 	while (new_string && new_string[i])
// 	{
// 		//printf("segment [%i] : `%s`\n", i ,new_string[i]);
// 		free(new_string[i]);
// 		i++;
// 	}
// 	if (new_string)
// 		free(new_string);
// 	return (0);
// }
