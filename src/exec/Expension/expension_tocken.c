/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expension_tocken.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 18:03:45 by ofilloux          #+#    #+#             */
/*   Updated: 2025/05/14 18:38:32 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

static int	handle_dollar_expension(t_data *data, char *str_sub, char *dst)
{
	char	*var_name;
	char	*var_value;
	int		copied_len;

	copied_len = 0;
	var_name = get_var_name(str_sub, 0);
	var_value = ft_getenv(data->env_list, var_name);
	if (ft_strcmp(var_name, "?") == 0)
		var_value = ft_itoa(data->exit_status);
	if (var_value)
		copied_len = ft_strlcpy(dst, var_value, ft_strlen(var_value) + 1);
	if (ft_strcmp(var_name, "?") == 0)
		ft_free((void **) &var_value);
	ft_free((void **) &var_name);
	return (copied_len);
}

static char *process_expension_loop(t_data *data, char *str, char *expd_token,
									t_quote *quotes)
{
	char *var_name;
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		quote_increment(str, i, quotes);
		if ((quotes->dbl_quote % 2 == 1 || quote_and_acc_are_closed(quotes)) \
			 && str[i] == '$')
		{
			var_name = get_var_name(str + i, 0);
			j += handle_dollar_expension(data, str + i, expd_token + j);
			if (str[i + 1] == '{')
				i += ft_strlen(var_name) + 3;
			else
				i += ft_strlen(var_name) + 1;
			ft_free((void **)&var_name);
		}
		else
			expd_token[j++] = str[i++];
	}
	return (expd_token);
}

char	*expend_token(t_data *data, char *str)
{
	t_quote	quotes;
	char	*expd_token;
	int		expd_token_len;
	char	*ret_tocken;

	expd_token_len = get_expended_tocken_len(data, str);
	expd_token = malloc(sizeof(char) * (expd_token_len + 1));
	if (!expd_token)
		return (printf("Error : malloc expension\n"), NULL);
	expd_token[expd_token_len] = '\0';
	init_quotes(&quotes);
	ret_tocken = process_expension_loop(data, str, expd_token, &quotes);
	return (ret_tocken);
}

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
		if((quotes.dbl_quote % 2 == 1 || quote_and_acc_are_closed(&quotes)) && str[i] == '$')
		{
			var_name = get_var_name(str, i);
			var_value = ft_getenv(data->env_list, var_name);
			if (ft_strcmp(var_name, "?") == 0)
				var_value = ft_itoa(data->exit_status);
			if (var_value)
				j += ft_strlcpy(expd_token + j, var_value, (size_t) ft_strlen(var_value) + 1); // +1 pour '\0'
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
