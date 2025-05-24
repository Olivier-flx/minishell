/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expension_tocken.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 18:03:45 by ofilloux          #+#    #+#             */
/*   Updated: 2025/05/24 12:23:54 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

static int	handle_expension(t_data *data, char **var_name, char *expd_token_j)
{
	char	*var_value;
	int		copied_len;

	copied_len = 0;
	var_value = ft_getenv(data->env_list, *var_name);
	if (ft_strcmp(*var_name, "?") == 0)
		var_value = ft_itoa(data->exit_status);
	if (var_value)
		copied_len = ft_strlcpy(expd_token_j, var_value, ft_strlen(var_value) + 1);
	else
		copied_len = ft_strlcpy(expd_token_j, "$", 2);
	if (ft_strcmp(*var_name, "?") == 0)
		ft_free((void **) &var_value);
	ft_free((void **) var_name);
	return (copied_len);
}

static	void	increment_i_expension_loop(char *var_name, char *str, int	*i)
{
	int var_name_len;

	var_name_len = 0;
	var_name_len = ft_strlen(var_name);
	if (str[(*i) + 1] && str[(*i) + 1] == '{')
				(*i) += var_name_len + 3;
			else
				(*i) += var_name_len + 1;
}

static char	*process_expension_loop(t_data *data, char *str, char **expd_token,
									t_quote *quotes)
{
	char *var_name;
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str && str[i])
	{
		quote_increment(str, i, quotes);
		if ((quotes->dbl_quote % 2 == 1 || quote_and_acc_are_closed(quotes)) \
			 && str[i] == '$')
		{
			get_var_name(&var_name, str + i, 0);
			if(var_name)
			{
				printf("process_expension_loop var_name = %s\n",var_name);
				increment_i_expension_loop(var_name, str, &i);
				j += handle_expension(data, &var_name, (*expd_token) + j);
			}
			else
			{
				printf("process_expension_loop var_name = NULL\n");
				(*expd_token)[j++] = str[i++];
				continue;
			}
		}
		else
		{
			(*expd_token)[j++] = str[i++];
			printf("(*expd_token)[%i] = %c, str[%i] = %c \n",  j -1, (*expd_token)[j- 1], i- 1,  str[i - 1]); // @debug
		}
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
	printf("expend_token --> expd_token_len = %i\n", expd_token_len);// @debug
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
	ret_tocken = process_expension_loop(data, str, &expd_token, &quotes);
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
