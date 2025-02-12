/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_input_token.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 17:57:45 by ofilloux          #+#    #+#             */
/*   Updated: 2025/02/12 16:44:37 by ofilloux         ###   ########.fr       */
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


t_input_tocken *create_token(char **str, int type, int i, t_quote quotes)
{
	t_input_tocken	*token;

	token = malloc(sizeof(t_input_tocken));
	if (!token)
			return (NULL);
	token->content = *str;
	token->type = type;
	token->index = i;
	token->len = s_len(*str);
	token->quotes = quotes;
	return (token);
}

char	*operator_sdup(char *src, int i)
{
	char	*operador;

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
	return (operador);
}

/// Operator to handle
/// <
/// >
/// |
/// $
/// <<
/// >>
static int	operator_list(char *src, int i, t_list **cmd_list)
{
	char			*operador;
	char			**operador_to_arr;
	t_input_tocken	*token;

	token = NULL;
	operador = operator_sdup(src, i);
	if (operador != NULL)
	{
		operador_to_arr = malloc (2 * sizeof (char *))
		if (!operador_to_arr)
			return (free(operator), 0);
		operador_to_arr[0] = operador;
		operador_to_arr[1] = NULL;
		token = create_token(&operador_to_arr, OPERATOR, i, (t_quote) {0});
		return (add_to_list(cmd_list, token), token->len);
	}
	return (0);
}
		//*token = (t_input_tocken){operador, false, false, true, false};

int	create_input_to_commands(char *src, t_list **cmd_list, t_data *data)
{
	t_quote		quotes;
	int			chunks;
	int			i;

	if (!src)
		return (1); //Error
	init_operador_var(&quotes, NULL, &i);
	chunks = count_operador(src) + 1; // no util de momento
	set_operator_char_i_struc_arr(src, &(data->operator_char_i));
	while (src[i])
	{
		if(int_var_in_arr(i, data->operator_char_i))
			i += operator_list(src, i, cmd_list); // se puede cambiar facilmente si se quere una lista para oper y una para argvs
		else
		{
			while (!int_var_in_arr(i, data->operator_char_i))

		}





		increment_quotes(src, i, &quotes);
		if (chunks >= 0) // à supprimer par la suite--> juste pour compile
			printf("chunks");
		//if (quotes.dbl % 2 == 1)
		//	i += is_var_call(src, i, cmd_list);
		if (quotes.sgl % 2 == 0  && quotes.dbl % 2 == 0)
		{
			i += is_operator(src, i);
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

/*
////PREVIOUS VERSION//
int	create_input_to_commands(char *src, t_list **cmd_list)
{
	int		in_sgl_quote;
	int		in_dbl_quote;
	bool	in_word;
	int		i;
	t_quote		quote;

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
*/
