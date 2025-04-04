/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_set_of_char.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 11:18:50 by ofilloux          #+#    #+#             */
/*   Updated: 2025/04/04 15:55:14 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

static int	ft_segment_count(char *s)
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
			//printf("segment incremented at s[%i] = %c\n", i, s[i]); // @debug
			i += is_seperator(s, i, &quote);
			in_segment = false;
			continue;
		}
		else if (is_seperator(s, i, &quote) == 0 && !in_segment) // si ce n'est pas un operateur
		{
			count++;
			//printf("segment incremented at s[%i] = %c\n", i, s[i]); // @debug
			in_segment = true;
		}
		i++;
	}
	return (count);
}

static int	ft_segment_len(int i, char *s, t_quote *quote, t_int_array *separators)
{
	int		len;

	len = 0;
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

static void	init_var_ft_new_string_arr(int *i, int *segment_i, int *flag)
{
	*i = 0;
	*segment_i = 0;
	*flag = 0;
}



static char	**ft_new_string_arr(char *s, char **ns_ar, int nb_segment, t_int_array *separators)
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
	int		tokens_number;
	int i = 0; //@debug

	ns_ar = NULL;
	if (s == NULL)
		return (NULL);
	set_separator_char_i_struc_arr(s, &(data->token_separators_char_i));
	tokens_number = ft_segment_count(s);
	printf("tokens_number = %i\n", tokens_number); // @debug
	ns_ar = malloc(((1 + tokens_number)) * sizeof(char *));
	if (!ns_ar)
		return (0);
	ns_ar = ft_new_string_arr(s, ns_ar, tokens_number, &(data->token_separators_char_i));

	//@debug -----------
	printf("Tockens : ");
	fflush(stdout);
	while (ns_ar && ns_ar[i])
	{
		printf("[%i],`%s`;  ", i ,ns_ar[i]);
		i++;
	}
	printf("\n\n");
	//@debug -----------

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
