/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expension.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 17:38:16 by ofilloux          #+#    #+#             */
/*   Updated: 2025/06/04 13:20:46 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

void	get_classic_var_name(char **var_name, char *str, int i)
{
	int	var_name_len;

	var_name_len = 0;
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_' || str[i] == '?'))
	{
		i++;
		var_name_len ++;
	}
	if (var_name_len == 0)
		return ;
	*var_name = malloc(sizeof(char) * (var_name_len + 1));
	if (!(*var_name))
		return ;
	(*var_name)[var_name_len] = '\0';
	ft_strlcpy(*var_name, str + i - var_name_len, var_name_len + 1); // man : Note that a byte for the NUL should be included in size.
}

bool	get_var_name(char **var_name, char *str, int i)
{
	*var_name = NULL;
	if (str[i++] != '$')
		return (false);
	if (str[i] == '{')
		get_var_name_in_accolade(var_name, str, i + 1);
	else
		get_classic_var_name(var_name,str, i);
	if (var_name)
		return (true);
	return (false);
}

void	handle_question_mark_set_k(t_data *data, char **var_name, \
								char **var_value, int *k)
{
	if (!var_name)
		return ;
	if (ft_strcmp(*var_name, "?") == 0)
		*var_value = ft_itoa(data->exit_status);
	*k += ft_strlen(*var_value);
	if (ft_strcmp(*var_name, "?") == 0)
		ft_free((void **) var_value);
}

int	handle_empty_var_name(char *str, int i)
{
	int	k;

	k = 1;
	if (str[(i)] && !str[(i) + 1])
	{
		//*var_value = ft_strdup("$");
		return (1);
	}
	if (str[(i)] && str[(i) + 1] && (str[(i) + 1] == '{' /* || is_quote(str[(i) + 1]) */))
		return (3);
	while (str[i] && str[i] != '$' && !is_quote(str[i]) && !ft_isalnum(str[i]))
	{
		k++;
		i++;
	}
	return (k);
}

//V2
int get_expended_tocken_len(t_data *data, char *s)
{
	int		i;
	int		k;
	t_quote qts;

	i = 0;
	k = 0;
	init_quotes(&qts);
	while (s[i])
	{
		//printf("get_expended_tocken_len s[%i] = %c\n", i, s[i]); //@debug
		if (skip_quote(&i, &k, &qts, s) || skip_dollar_quote(&i, &k ,&qts, s)) // @test id 2
		{
			//printf("ENTRA\n"); //@debug
			continue ;
		}
		if (s[i] == '$' && (qts.dbl_qt % 2 == 1 \
			|| qts_acc_closed(&qts)) \
			&& (ft_isalnum(s[i + 1]) || s[i + 1] == '_' || s[i + 1] == '?')
		)
		{
			get_len_and_increment_i(data, s, &i, &k);
			continue ;
		}
		if (handle_invalid_dollar(&i, &k, &qts, s))
			continue ;
		i++;
		k++;
	}
	return k;
}

//V1
/* int get_expended_tocken_len(t_data *data, char *str)
{
	int	i;
	int k;
	t_quote	quotes;

	init_quotes(&quotes);
	i = 0;
	k = 0;
	while (str[i])
	{
		quote_increment(str, i, &quotes);
		if ((quotes.dbl_qt % 2 == 1 || qts_acc_closed(&quotes)) \
			&& str[i] == '$')
		{
			get_len_and_increment_i(data, str, &i, &k);
			printf("get_expended_tocken_len -> k = %i\n", k);// @debug
		}
		else if (is_quote(str[i]) && ( quotes.sgl_qt % 2 == 1 || quote_are_closed(&quotes))) // @ debug @ test id 1
			i++;
		else
		{
			i++;
			k++;
		}
	}
	return (k);
} */

/* int get_expended_tocken_len(t_data *data, char *str)
{
	int		i = 0;
	int		k = 0;
	t_quote	quotes;
	bool	was_quotes;

	init_quotes(&quotes);
	while (str[i])
	{
		was_quotes = bool_quote_increment(str, &i, &quotes);
		if (was_quotes)
			continue ;
		if (str[i] == '$' && quote_are_closed(quotes) && is_quote(str[i + 1]))
		{
			i++;
			bool_quote_increment(str, &i, &quotes);
			continue ;
		}
		if (str[i] == '$'
			&& (quotes.dbl_qt % 2 == 1 || qts_acc_closed(&quotes)))
		{
			get_len_and_increment_i(data, str, &i, &k);
			continue ;
		}
		if (str[i] == '$' && quotes.sgl_qt % 2 == 0)
		{
			i++;
			if (str[i]
				&& !ft_isalnum(str[i])
				&& str[i] != '_'
				&& str[i] != '?')
				i++;
			continue ;
		}
		i++;
		k++;
	}
	return (k);
} */

// int get_expended_tocken_len(t_data *data, char *str)
// {
// 	int	i;
// 	int k;
// 	t_quote	quotes;
// 	bool	was_quotes;

// 	init_quotes(&quotes);
// 	i = 0;
// 	k = 0;
// 	was_quotes = false;
// 	while (str[i])
// 	{
// 		was_quotes = bool_quote_increment(str, &i, &quotes);
// 		if ((quotes.dbl_qt % 2 == 1 || qts_acc_closed(&quotes))
// 			&& str[i] == '$' && !was_quotes)
// 		{
// 			get_len_and_increment_i(data, str, &i, &k);
// 			printf("get_expended_tocken_len -> k = %i\n", k); // @debug
// 		}
// 		else if (was_quotes || (str[i] == '$' && is_quote(str[i + 1]))) // @ debug @ test id 1 // PROBLEME ICI avec echo $""
// 			i++;
// 		else
// 		{
// 			i++;
// 			k++;
// 		}
// 	}
// 	return (k);
// }
/// Si le nom de la variable n'est pas correct, on doit retourner le message [-bash: ${world${test}}: bad substitution]
