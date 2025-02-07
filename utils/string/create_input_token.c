/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_input_token.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 17:57:45 by ofilloux          #+#    #+#             */
/*   Updated: 2025/02/07 18:14:53 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"


/////// NOT USED ///// 26-01-2024
int	segment_count(char *src)
{
	int		i;
	int		count;
	bool	in_word;
	bool	in_quotes;

	i = 0;
	count = 0;
	in_word = false;
	in_quotes = false;
	while (src[i] != '\0')
	{
		if (src[i] == '\'' && in_quotes)
			in_quotes = false;
		else if (src[i] == '\'' && !in_quotes)
		{
			in_quotes = true;
			count++;
		}
		else if (src[i] == ' ')
			in_word = false;
		else if (src[i] != ' ' && !in_quotes && !in_word)
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
// static int	is_var_call(char *src, int i, t_list **cmd_list)
// {
// 	int		j;
// 	int		k;
// 	char	*var_name;

// 	if (!src)
// 		return (0);
// 	j = 0;
// 	k = 0;
// 	if (src[i] == '$')
// 	{
// 		while (src[i] && (src[i] != ' ' && src[i] != '\t' && src[i] != '\n'))
// 		{//contar las caracteres de la variable
// 			j++;
// 			i++;
// 		}
// 		i++;
// 	}
// 	var_name = malloc((j + 1) * sizeof(char));
// 	if (!var_name)
// 		return (simple_error_msg("varName_malloc error"), -1);
// 	while (src[i] && k < j)
// 		var_name[k++] = src[i++];
// 	return (add_to_list(cmd_list, &((t_input_tocken){var_name,false,false,true,true})), j + 1);
// }
//ret j + 1 por el "$"

/// Operator to handle
/// <
/// >
/// |
/// $
/// <<
/// >>
static int	is_operator(char *src, int i, t_list **cmd_list)
{
	char			*operador;
	t_input_tocken	*token;

	token = NULL;
	operador = NULL;

	if (src[i] == 124)
		operador = s_dup("|");
	else if (src[i] == '>' && src[i + 1] && src[i + 1] == '>')
		operador = s_dup(">>");
	else if (src[i] == '<' && src[i + 1] && src[i + 1] == '<')
		operador = s_dup("<<");
	else if (src[i] == '<')
		operador = s_dup("<");
	else if (src[i] == '>')
		operador = s_dup(">");

	if (operador != NULL)
	{
		token = malloc(sizeof(t_input_tocken));
		if (!token)
			return (-1);
		*token = (t_input_tocken){operador, false, false, true, false};
		return (add_to_list(cmd_list, token), s_len(operador));
	}
	return (0);
}

void	init_var(int *sgl_quote, int *dbl_quote, bool *in_word, int *i)
{
	*sgl_quote = 0;
	*dbl_quote = 0;
	*in_word = false;
	*i = 0;
}

int	create_input_to_commands(char *src, t_list **cmd_list)
{
	int		in_sgl_quote;
	int		in_dbl_quote;
	bool	in_word;
	int		i;

	init_var(&in_sgl_quote, &in_dbl_quote, &in_word, &i);

	if (!src)
		return (1); //Error

	while (src[i])
	{
		if (src[i] == '"' && in_sgl_quote % 2 == 0)
			in_dbl_quote++;
		if (src[i] == '\'' && in_dbl_quote % 2 == 0)
			in_sgl_quote++;
		//if (in_dbl_quote % 2 == 1)
		//	i += is_var_call(src, i, cmd_list);
		if (in_sgl_quote % 2 == 0  && in_dbl_quote % 2 == 0)
		{
			i += is_operator(src, i, cmd_list);
			//i += is_var_call(src, i, cmd_list); //create seg fault
		}


		/// TODO
			// Crear una funccion para poner los commandos entre operadores en la lista

		//i++;
	}
	printf("la list est ici ->\n");
	print_list(cmd_list);

	//printf("token test = %s\n", (*line)->content);

	//free ((*line)->word);
	return (0);
}
