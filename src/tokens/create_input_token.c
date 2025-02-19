/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_input_token.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 17:57:45 by ofilloux          #+#    #+#             */
/*   Updated: 2025/02/19 15:28:55 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"


//	i = 9
//	varname = "rao"; --> j = 3;
//	i = 12
// put var name into the list of commands;
// static int	is_var_call(char *src, int i, t_dlist **cmd_list)
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


t_input_tocken	*create_token(char ***str, int type, int i, t_quote quotes)
{
	t_input_tocken	*token;

	token = malloc(sizeof(t_input_tocken));
	if (!token)
		return (NULL);
	token->content = *str;
	token->type = type;
	token->index = i;
	if (type == OPERATOR)
		token->len = s_len(*str[0]);
	else
		token->len = 0; //TODO
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
static int	operator_list(char *src, int i, t_dlist **cmd_list)
{
	char			*operador;
	char			**operador_to_arr;
	t_input_tocken	*token;

	token = NULL;
	operador = operator_sdup(src, i);
	if (operador != NULL)
	{
		operador_to_arr = malloc (2 * sizeof (char *));
		if (!operador_to_arr)
			return (free(operador), 0);
		operador_to_arr[0] = operador;
		operador_to_arr[1] = NULL;
		token = create_token(&operador_to_arr, OPERATOR, i, (t_quote) {0});
		return (add_to_list(cmd_list, token), s_len(operador));
	}
	return (0);
}
		//*token = (t_input_tocken){operador, false, false, true, false};

int	create_input_to_commands(char *src, t_dlist **cmd_list, t_data *data)
{
	t_quote			quotes;
	int				chunks_n;
	int				i;
	int				j = 0;
	char			**chunk;
	t_input_tocken	*token;

	token = NULL;

	if (!src)
		return (1); //Error
	init_operador_var(&quotes, &j, &i);
	chunks_n = count_operador(src) + 1; // no util de momento
	set_ope_char_i_struc_arr(src, &(data->ope_char_i));
	while (src[i])
	{
		if(int_var_in_arr(i, &(data)->ope_char_i))
			i += operator_list(src, i, cmd_list); // se puede cambiar facilmente si se quere una lista para oper y una para argvs
		else
		{
			increment_quotes(src, i, &quotes);
			if(data->ope_char_i.size > 0)
			{
				printf("(data->ope_char_i).array[j] = %i\n",data->ope_char_i.size);
				chunk = split_quoted(ft_substr(src, i, (data->ope_char_i).array[j]), ' '); // remplacar luego con soporte a dbl quote
				i += data->ope_char_i.array[j] - i;
				j++;

/*redondant*/	token = create_token(&chunk, CMD, i, (t_quote) {0});
/*redondant*/	add_to_list(cmd_list, token);
			}
			else
			{
				chunk = split_quoted(ft_substr(src, i, s_len(src)), ' '); // remplacar luego con soporte a dbl quote
/*redondant*/	token = create_token(&chunk, CMD, i, (t_quote) {0});
/*redondant*/	add_to_list(cmd_list, token);
			}
				break ;
		}
		i++;


		if (chunks_n > 0) // à supprimer par la suite--> juste pour compile
			printf("chunks\n");
		//if (quotes.dbl % 2 == 1)
		//	i += is_var_call(src, i, cmd_list);
		// if (quotes.sgl % 2 == 0  && quotes.dbl % 2 == 0)
		// {
		// 	i += is_operator(src, i);
		// 	//i += is_var_call(src, i, cmd_list); //create seg fault
		// }




		/// TODO
			// Crear una funccion para poner los commandos entre operadores en la lista

		//i++;
	}
	printf("la list est ici ->\n");
	print_dlist(cmd_list);

	//printf("token test = %s\n", (*line)->content);

	//free ((*line)->word);
	return (0);
}
