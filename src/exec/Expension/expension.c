/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expension.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 17:38:16 by ofilloux          #+#    #+#             */
/*   Updated: 2025/05/24 10:16:41 by ofilloux         ###   ########.fr       */
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

void	get_var_name(char **var_name, char *str, int i)
{
	*var_name = NULL;
	if (str[i++] != '$')
		return ;
	if (str[i] == '{')
		get_var_name_in_accolade(var_name, str, i + 1);
	else
		get_classic_var_name(var_name,str, i);
}

static void	handle_question_mark_set_k(t_data *data, char **var_name, \
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

/* static void	get_len_and_increment_i(t_data *data, char *str, int *i, int *k)
{
	char	*var_name;
	char	*var_value;

	get_var_name(&var_name, str, *i);
	// if(!var_name)
	// {
	// 	(*i)++;
	// 	return ;
	// }
	if (str[(*i) + 1] && str[(*i) + 1] == '{')
		(*i) += ft_strlen(var_name) + 3; // +1 pour le $ et les {}
	else
		(*i) += ft_strlen(var_name) + 1; // +1 pour le $
	var_value = ft_getenv(data->env_list, var_name);
	handle_question_mark_set_k(data, &var_name, &var_value, k);
	ft_free((void **) &var_name);

} */

static int	handle_empty_var_name(char *str, int *i, char **var_value)
{
	if (str[(*i)] && !str[(*i) + 1])
	{
		*var_value = ft_strdup("$");
		return (1);
	}
	if (str[(*i)] && str[(*i) + 1] && str[(*i) + 1] == '{')
		return (3);
	return (0);
}

static void	get_len_and_increment_i(t_data *data, char *str, int *i, int *k)
{
	char	*var_name;
	char	*var_value;

	var_name = NULL;
	get_var_name(&var_name, str, *i);
	if (!var_name)
		*k += handle_empty_var_name(str, i, &var_value);
	if (str[(*i) + 1] && str[(*i) + 1] == '{')
		(*i) += 3; // +1 pour le $ et les {}
	else
		(*i) += 1; // +1 pour le $
	if(var_name)
	{
		(*i) += ft_strlen(var_name);
		var_value = ft_getenv(data->env_list, var_name);
		handle_question_mark_set_k(data, &var_name, &var_value, k);
		ft_free((void **) &var_name);
	}
}

int get_expended_tocken_len(t_data *data, char *str)
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
		if((quotes.dbl_quote % 2 == 1 || quote_and_acc_are_closed(&quotes)) \
			&& str[i] == '$')
			get_len_and_increment_i(data, str, &i, &k);
		else
		{
			i++;
			k++;
		}
	}
	return (k);
}
/// Si le nom de la variable n'est pas correct, on doit retourner le message [-bash: ${world${test}}: bad substitution]

int	expend_chunk(t_data *data, t_chunk *chunk)
{
	int	i;
	char *ret_val;

	ret_val = NULL;
	i = 0;
	while (chunk->tokens && chunk->tokens[i])
	{
		ret_val = expend_token(data, chunk->tokens[i]);
		ft_free((void **) &ret_val);
		if (!ret_val)
			return (1); // @confirm : à voir s'il y a un bug d'expension, s'il faut arrêter l'expension du rest ou non
		i++;
	}
	return (0);
}

int	expend_all(t_data *data)
{
	int		ret_val;
	t_dlist	*i_node;

	i_node = data->cmd_list;
	ret_val = 0;
	while (i_node)
	{
		expend_chunk(data, (t_chunk *)i_node->content);
		if (ret_val != 0)
			return (ret_val); // @confirm : à voir s'il y a un bug d'expension, s'il faut arrêter l'expension du rest ou non
		i_node = i_node->next;
	}
	return (ret_val);
}
