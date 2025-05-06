/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expension.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 17:38:16 by ofilloux          #+#    #+#             */
/*   Updated: 2025/05/06 09:59:32 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

// int get_var_name_len(char *str, int i)
// {
// 	int		k;
// 	bool	escaped;
// 	bool	accolade;

// 	k = 0;
// 	escaped = false;
// 	accolade = false;
// 	while (str[++i])
// 	{
// 		escaped = false;
// 		if (str[i] == '\\')
// 			escaped = true;
// 		if (str[i] == '{')
// 			accolade = true;
// 		if(!escaped && 0 == ft_isalnum(str[i])  && str[i] != '_')
// 			return (k);
// 		k++;
// 	}
// 	return (k);
// }

bool	unsuported_accolade_operator(char c)
{
	if (c == '-' || c == '+' || c == ':' || c == '=' || c == '%' || c == '*' || \
			c == '!' || c == '?')
	{
		printf("Warning : unsuported minishell operator `%c` in ${}\n", c);
		return(true);
	}
	return (false);
}

char	*get_var_name_in_accolade(char *str, int i)
{
	int	var_name_len;
	char *var_name;

	var_name_len = 0;
	var_name = NULL;
	while (str[i] && str[i] != '}')
	{
		if (unsuported_accolade_operator(str[i]))
			return (NULL);
		i++;
		var_name_len ++;
	}
	var_name = malloc(sizeof(char) * (var_name_len + 1));
	if (!var_name)
		return (NULL);
	var_name[var_name_len] = '\0';
	ft_strlcpy(var_name, str + i - var_name_len, var_name_len + 1);
	return (var_name);
}

char	*get_classic_var_name(char *str, int i)
{
	int	var_name_len;
	char *var_name;

	var_name_len = 0;
	var_name = NULL;
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
	{
		i++;
		var_name_len ++;
	}
	var_name = malloc(sizeof(char) * (var_name_len + 1));
	if (!var_name)
		return (NULL);
	var_name[var_name_len] = '\0';
	ft_strlcpy(var_name, str + i - var_name_len, var_name_len + 1); // man : Note that a byte for the NUL should be included in size.
	return (var_name);
}

char	*get_var_name(char *str, int i)
{
	char	*var_name;

	if (str[i++] != '$')
		return (printf("Error : get_var_name not a var input\n"), NULL);
	if (str[i] == '{')
		var_name = get_var_name_in_accolade(str, i + 1);
	else
		var_name = get_classic_var_name(str, i);
	return (var_name);

}
int get_expended_tocken_len(t_data *data, char *str)
{
	int	i;
	int k;
	t_quote	quotes;
	char	*var_name;
	char	*var_value;

	init_quotes(&quotes);
	i = 0;
	k = 0;
	while (str[i])
	{
		quote_increment(str, i, &quotes);
		if((quotes.dbl_quote % 2 == 1 || quote_are_closed(&quotes)) && str[i] == '$')
		{
			var_name = get_var_name(str, i);
			var_value = ft_getenv(data->env_list, var_name);
			k += ft_strlen(var_value);
			if (str[i + 1] && str[i + 1] == '{')
				i += ft_strlen(var_name) + 3; // +1 pour le $ et les {}
			else
				i += ft_strlen(var_name) + 1; // +1 pour le $
			free(var_name);
		}
		else
		{
			i++;
			k++;
		}
	}
	return (k);
}

/// Si le nom de la variable n'est pas correct, on doit retourner le message [-bash: ${world${test}}: bad substitution]

char	*expend_token(t_data *data, char *str)
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
		if((quotes.dbl_quote % 2 == 1 || quote_are_closed(&quotes)) && str[i] == '$')
		{
			var_name = get_var_name(str, i);
			var_value = ft_getenv(data->env_list, var_name);

			if (var_value)
			{
				j += ft_strlcpy(expd_token + j, var_value, (size_t) ft_strlen(var_value) + 1); // +1 pour '\0'
				//free(var_value); // not necesary because free later in ft_free_env (env_utils.c:25)
			}
			if (str[i + 1] && str[i + 1] == '{')
				i += ft_strlen(var_name) + 3; // +1 pour le $ et les {}
			else
				i += ft_strlen(var_name) + 1; // +1 pour le $
			free(var_name);
		}
		else
			expd_token[j++] = str[i++];
	}
	return (expd_token);
}

int	expend_chunk(t_data *data, t_chunk *chunk)
{
	int	i;
	char *ret_val;

	ret_val = NULL;
	i = 0;
	while (chunk->tokens && chunk->tokens[i])
	{
		ret_val = expend_token(data, chunk->tokens[i]);
		printf("chunk->tokens[%i] = `%s` --> extended = `%s`\n",i, chunk->tokens[i], ret_val); // @debug
		free(ret_val); // @debug
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
