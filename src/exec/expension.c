/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expension.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 17:38:16 by ofilloux          #+#    #+#             */
/*   Updated: 2025/05/01 09:34:23 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	get_variable_count(char *str)
{
	while
}

int get_var_name_len(char *str, int i)
{
	int		k;
	bool	escaped;
	bool	accolade;

	k = 0;
	escaped = false;
	accolade = false;
	while (str[++i])
	{
		escaped = false;
		if (str[i] == '\\')
			escaped = true;
		if (str[i] == '{')
			accolade = true;
		if(!escaped && 0 == ft_isalnum(str[i])  && str[i] != '_')
			return (k);
		k++;
	}
	return (k);
}

int	get_var_name(char *str, int i)
{
	int len;
	char	*prefix;
	char	*var_name;
	char	*suffix;

}
int get_expended_tocken_len(t_data *data, char *str)
{

}

/// Si le nom de la variable n'est pas correct, on doit retourner le message [-bash: ${world${test}}: bad substitution]

char	*expend_token(t_data *data, char *str)
{
	int		i;
	int		j = 0;
	int		expd_token_len;
	char	*expd_token;
	char	*var_name;
	char	*var_value;
	t_quote	quotes;

	i = 0;
	expd_token_len = get_expended_tocken_len(data, str);
	expd_token = malloc(sizeof(char) * (1 + (expd_token_len)));
	if (!expd_token)
		return (printf("Error : malloc expension\n"), NULL);
	expd_token[expd_token_len] = '\0';
	init_quotes(&quotes);
	while (str[i])
	{
		quote_increment(str, i, &quotes);
		if((quotes.dbl_quote % 2 == 1 || quote_are_closed(&quotes)) && str[i] == '$')
		{
			var_name = get_var_name(str, i);
			var_value = ft_getenv(data->env_list, var_name);
			if (var_value)
			{
				j += ft_strlcpy(expd_token + j, var_value, ft_strlen(var_value) + 1); // +1 pour '\0'
				free(var_value);
			}
			i += ft_strlen(var_name) + 1; // +1 pour le $
			free(var_name);
		}
		else
			expd_token[j++] = str[i++];
	}
	return(expd_token)
}

int	expend_chunk(t_data *data, t_chunk *chunk)
{
	int	i;
	char *ret_val;

	ret_val = 0;
	i = 0;
	while (chunk->tokens && chunk->tokens[i])
	{
		ret_val = expend_token(data, chunk->tokens[i]);
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
