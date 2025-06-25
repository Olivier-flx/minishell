/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expension_tocken.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 18:03:45 by ofilloux          #+#    #+#             */
/*   Updated: 2025/06/09 17:41:41 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

static char	*process_exp_loop(t_data *data, char *str, char **expd_token, \
	t_quote *qts)
{
	int		i;
	int		j;
	char	*var_name;

	init_i_j (&i, &j);
	while (str && str[i])
	{
		if (skip_quote2(&i, NULL, qts, str) || \
			skip_dollar_quote(&i, NULL, qts, str))
		{
			(*expd_token)[j++] = str[i++];
			continue ;
		}
		if (str[i] == '$' && (qts->dbl_qt % 2 == 1 || qts_acc_closed(qts)) \
			&& get_var_name(&var_name, str + i, 0) && var_name && *var_name)
		{
			increment_i_expension_loop(var_name, str, &i);
			j += handle_expension(data, &var_name, *expd_token + j);
		}
		else if (handle_invalid_dollar(&i, &j, qts, str))
			(*expd_token)[j - 1] = '$';
		else
			(*expd_token)[j++] = str[i++];
	}
	return (*expd_token);
}

char	*expend_token(t_data *data, char *str)
{
	t_quote	quotes;
	char	*expd_token;
	int		expd_token_len;
	char	*ret_tocken;

	ret_tocken = NULL;
	expd_token_len = get_expended_tocken_len(data, str);
	if (expd_token_len < 0)
		return (NULL);
	if (expd_token_len >= 0)
	{
		expd_token = malloc(sizeof(char) * (expd_token_len + 1));
		if (!expd_token)
			return (printf("Error : malloc expension\n"), NULL);
		expd_token[expd_token_len] = '\0';
	}
	init_quotes(&quotes);
	ret_tocken = process_exp_loop(data, str, &expd_token, &quotes);
	return (ret_tocken);
}

// VERSION OK MAIS TROP LONGUE
/* static char *process_exp_loop(t_data *data, char *str, char **expd_token, \
	t_quote *qts)
{
	int		i;
	int		j;
	char	*var_name;

	init_i_j (&i, &j);
	while (str && str[i])
	{
		if (skip_quote(&i, qts, str) || skip_dollar_quote(&i, qts, str))
			continue ;
		if (str[i] == '$' && (qts->dbl_qt % 2 == 1 || qts_acc_closed(qts)))
		{
			if (get_var_name(&var_name, str + i, 0) && var_name && *var_name)
			{
				increment_i_expension_loop(var_name, str, &i);
				j += handle_expension(data, &var_name, *expd_token + j);
			}
			else
				(*expd_token)[j++] = str[i++];
		}
		else if (handle_invalid_dollar(&i, &j, qts, str))
			(*expd_token)[j - 1] = '$';
		else
			(*expd_token)[j++] = str[i++];
	}
	return (*expd_token);
} */

//V2
// static char	*process_exp_loop(t_data *data, char *str, char **expd_token,
// 									t_quote *quotes)
// {
// 	char	 *var_name;
// 	int		i;
// 	int		j;
// 	bool	was_qts;

// 	i = 0;
// 	j = 0;
// 	was_qts = false;
// 	while (str && str[i])
// 	{
// 		was_qts = bool_quote_increment(str, &i, quotes);
// 		if (was_qts)
// 			continue ;
// 		if (str[i] == '$'
// 			&& quotes->sgl_qt % 2 == 0
// 			&& quotes->dbl_qt % 2 == 0 && is_quote(str[i + 1]))
// 		{
// 			i++;
// 			bool_quote_increment(str, &i, quotes);
// 			continue ;
// 		}
// 		if ((quotes->dbl_qt % 2 == 1 || qts_acc_closed(quotes))
// 			 && str[i] == '$')
// 		{
// 			get_var_name(&var_name, str + i, 0);
// 			if (var_name)
// 			{
// 				increment_i_expension_loop(var_name, str, &i);
// 				j += handle_expension(data, &var_name, (*expd_token) + j);
// 			}
// 			else
// 				(*expd_token)[j++] = str[i++];
// 			continue ;
// 		}
// 		if (str[i] == '$' && quote_are_closed(quotes))
// 		{
// 			(*expd_token)[j++] = str[i++];
// 			if (str[i] && !ft_isalnum(str[i]) && str[i] != '_' && str[i] != '?')
// 				(*expd_token)[j++] = str[i++];
// 			continue ;
// 		}
// 		(*expd_token)[j++] = str[i++];
// 	}
// 	return (*expd_token);
// }

//V1
// static char	*process_exp_loop(t_data *data, char *str, char **expd_token,
// 									t_quote *quotes)
// {
// 	char	 *var_name;
// 	int		i;
// 	int		j;
// 	bool	was_qts;

// 	i = 0;
// 	j = 0;
// 	was_qts = false;
// 	while (str && str[i])
// 	{
// 		was_qts = bool_quote_increment(str, &i, quotes);
// 		if (was_qts)
// 			continue ;
// 		if (str[i] == '$' && quotes->dbl_qt % 2 == 0 && is_quote(str[i + 1]))
// 		{
// 			i++;
// 			/* laisse bool_quote_increment gérer la quote */
// 			bool_quote_increment(str, &i, quotes);
// 			continue ;
// 		}
// 		if ((quotes->dbl_qt % 2 == 1 || qts_acc_closed(quotes))
// 			 && str[i] == '$')
// 		{
// 			get_var_name(&var_name, str + i, 0);
// 			if (var_name)
// 			{
// 				increment_i_expension_loop(var_name, str, &i);
// 				j += handle_expension(data, &var_name, (*expd_token) + j);
// 			}
// 			else if (!str[i + 1] || quotes->dbl_qt % 2 == 1)
// 			{
// 				printf("ENTRA1 str[%i] = %c\n", i, str[i]); // @debug
// 				(*expd_token)[j++] = str[i++];
// 			}
// 			else
// 			{
// 				printf("ENTRA \n"); // @ debug
// 				i++;
// 			}
// 		}
// 		else if (was_qts)
// 			i++;
// 		else
// 		{
// 			printf("ENTRA3 str[%i] = %c\n", i, str[i]); // @debug
// 			(*expd_token)[j++] = str[i++];
// 		}
// 	}
// 	//printf("process_exp_loop *expd_token = %s\n", *expd_token); // @ debug
// 	return (*expd_token);
// }

/* char	*expend_token(t_data *data, char *str)
{
	int		i;
	int		j;
	int		expd_token_len;
	char	*expd_token;
	char	*var_name;
	char	*var_value;
	t_quote	quotes;

	i = 0;
	j = 0;
	expd_token_len = get_expended_tocken_len(data, str);
	expd_token = malloc(sizeof(char) * (1 + (expd_token_len)));
	if (!expd_token)
		return (printf("Error : malloc expension\n"), NULL);
	expd_token[expd_token_len] = '\0';
	init_quotes(&quotes);
	var_value = NULL;
	var_name = NULL;
	while (str[i])
	{
		quote_increment(str, i, &quotes);
		if ((quotes.dbl_qt % 2 == 1 || qts_acc_closed(&quotes)) && str[i] == '$')
		{
			var_name = get_var_name(str, i);
			var_value = ft_getenv(data->env_list, var_name);
			if (ft_strcmp(var_name, "?") == 0)
				var_value = ft_itoa(data->exit_status);
			if (var_value)
				j += ft_strlcpy(expd_token + j, var_value,
					(size_t) ft_strlen(var_value) + 1); // +1 pour '\0'
			if (ft_strcmp(var_name, "?") == 0)
				ft_free((void **) &var_value);
			if (str[i + 1] && str[i + 1] == '{')
				i += ft_strlen(var_name) + 3; // +1 pour le $ et les {}
			else
				i += ft_strlen(var_name) + 1; // +1 pour le $
			ft_free((void **) &var_name);
		}
		else
			expd_token[j++] = str[i++];
	}
	return (expd_token);
} */
