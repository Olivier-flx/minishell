/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_input_token.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 17:57:45 by ofilloux          #+#    #+#             */
/*   Updated: 2025/01/28 08:43:54 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"


/////// NOT USED ///// 26-01-2024
int	segment_count(char *src);
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
		else if (s[i] == ' ')
			in_word = false;
		else if (s[i] != ' ' && !in_quotes && !in_word)
		{
			count++;
			in_word = true;
		}
		i++;
	}
	return (count);
}

//	i = 9
//	varname = "rao"; --> j = 3;
//	i = 12
// put var name into the list of commands;
static int	is_var_call(src, i, cmd_list)
{
	int		j;
	int		k;
	char	var_name

	if (!src)
		return (0);
	j = 0;
	k = 0;
	if (src[i] == '$')
	{
		while (s[i] && (s[i] != ' ' || s[i] != '\t' || s[i] != '\n'))
		{
			j++;
			i++;
		}
		i++;
	}
	var_name = malloc((j + 1) * sizeof(char));
	if (!var_name)
		return (simple_error_msg("varName_malloc error"))
	while (s[i] && k < j)
		var_name[k++] = S[i++];
	return(add_to_list(cmd_list,{var_name,false,false,true,true}), j + 1);
}
//ret j + 1 por el "$"

/// Operator to handle
/// <
/// >
/// |
/// $
/// <<
/// >>
static int	is_operator(char *src,int i, t_list cmd_list)
{
	if (src[i] == '<')
		return(add_to_list(cmd_list,{sdup("<"), NULL, false, false, true, false}), 1);
		// ver si hay manera más bonita rellenar el t_input_tocken
	if (src[i] == '>')
		return(add_to_list(cmd_list,{sdup(">"), NULL, false, false, true, false}), 1);
	if (src[i] == '|')
		return(add_to_list(cmd_list,{sdup("|"), NULL, false, false, true, false}), 1);
	if (src[i] == '>' && s[i + 1] && s[i + 1] =='>')
		return(add_to_list(cmd_list,{sdup(">>"), NULL, false, false, true, false}), 2);
	if (src[i] == '<' && s[i + 1] && s[i + 1] =='<')
		return(add_to_list(cmd_list,{sdup("<<", NULL, false, false, true, false}), 2);
	return (0);
}

inline init_var (int *a, int *b, int *c, bool *d, int *i)
{
	*a = 0;
	*b = 0;
	*c = 0;
	*d = false;
	*i = 0;
}

int	create_input_to_commands(char *src, t_list **cmd_list)
{
	int		segment_number;
	int		in_sgl_quote;
	int		in_dbl_quote;
	bool	in_word;
	int		i;

	init_var  (&segment_number, in_sgl_quote,in_dbl_quote, in_word, i )

	if (!src || !line)
		return (1); //Error

	while(src[i])
	{
		if (s[i] == '"' && in_sgl_quote % 2 == 0)
			in_double_quote++;
		if (s[i] == '\'' && in_dbl_quote % 2 == 0)
			in_single_quote++;
		if (in_dbl_quote % 2 == 1)
			i += is_var_call(src, i, cmd_list);
		if( in_sgl_quote % 2 == 0  && in_dbl_quote % 2 == 0)
		{
			i += is_operator(src, i, cmd_list);
			i += is_var_call(src, i, cmd_list);
		}


		/// TODO
			// Crear una funccion para poner los commandos entre operadores en la lista

		i++;
	}



	segment_number = segment_count(src);

	//(*line)->word = s_dup(src);
	input_to_token(line);








	(*line)->content = src;
	printf("token test = %s\n", (*line)->content);

	//free ((*line)->word);
	return (0);
}
