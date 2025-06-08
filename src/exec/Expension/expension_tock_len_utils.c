/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expension_tock_len_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 20:36:31 by ofilloux          #+#    #+#             */
/*   Updated: 2025/06/08 09:08:57 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

// Obtenir la variable de et incrémenter i en fonction
void	get_len_and_increment_i(t_data *data, char *str, int *i, int *k)
{
	char	*var_name;
	char	*var_value;

	var_name = NULL;
	if (!get_var_name(&var_name, str, *i))
		*k += handle_empty_var_name(str, *i);
	if (str[(*i) + 1] && (str[(*i) + 1] == '{'))
		(*i) += 3;
	else
		(*i) += 1;
	if (var_name)
	{
		(*i) += ft_strlen(var_name);
		var_value = ft_getenv(data->env_list, var_name);
		handle_question_mark_set_k(data, &var_name, &var_value, k);
		ft_free((void **) &var_name);
	}
}

// V2
// Si on rencontre un guillemet, on le marque et on saute
bool	skip_quote(int *i, int *k, t_quote *quotes, char *str)
{
	if (bool_quote_increment(str, i, quotes, true))
	{
		if (k)
			(*k)++;
		return (true);
	}
	return (false);
}
// V1
// // Si on rencontre un guillemet, on le marque et on saute
// bool skip_quote(int *i, t_quote *quotes, char *str)
// {
// 	return (bool_quote_increment(str, i, quotes));
// }

//Cas `$` suivi de quote hors contexte de quote fermée
bool	skip_dollar_quote(int *i, int *k, t_quote *quotes, char *str)
{
	if (str[*i] == '$' && quote_are_closed(quotes) \
		&& is_quote(str[*i + 1]))
	{
		(*i)++;
		bool_quote_increment(str, i, quotes, true);
		if (k)
			(*k)++;
		return (true);
	}
	return (false);
}

//Cas `$` suivi de quote hors contexte de quote fermée
// @test id5
bool	skip_quote2(int *i, int *k, t_quote *quotes, char *str)
{
	if (bool_quote_increment(str, i, quotes, false))
	{
		if (k)
			(*k)++;
		return (true);
	}
	return (false);
}
// V1
// // Si on rencontre un guillemet, on le marque et on saute
// bool skip_quote(int *i, t_quote *quotes, char *str)
// {
// 	return (bool_quote_increment(str, i, quotes));
// }

// $ isolé ou invalide hors simple-quote : on compte 1 char
bool	handle_invalid_dollar(int *i, int *k, t_quote *quotes, char *str)
{
	if (str[*i] == '$' && quotes->sgl_qt % 2 == 0)
	{
		(*i)++;
		(*k)++;
		return (true);
	}
	return (false);
}
