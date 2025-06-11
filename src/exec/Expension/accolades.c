/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   accolades.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 16:59:46 by ofilloux          #+#    #+#             */
/*   Updated: 2025/05/12 17:00:05 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

bool	unsuported_accolade_operator(char *str, int i)
{
	if (str[i] == '-' || str[i] == '+' || str[i] == ':' \
		|| str[i] == '=' || str[i] == '%' || str[i] == '*' || \
		str[i] == '!' || (str[i] == '?' && str[i + 1] != '}'))
	{
		printf("Warning : unsuported minishell operator `%c` in ${}\n", str[i]);
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
		if (unsuported_accolade_operator(str, i))
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
