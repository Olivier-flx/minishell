/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   accolades.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 16:59:46 by ofilloux          #+#    #+#             */
/*   Updated: 2025/06/08 09:03:51 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

bool	unsuported_accolade_operator(char *str, int i)
{
	if (str[i] == '-' || str[i] == '+' || str[i] == ':' \
		|| str[i] == '=' || str[i] == '%' || str[i] == '*' || \
		str[i] == '!' || (str[i] == '?' && str[i + 1] != '}'))
	{
		printf("Warning : unsuported minishell operator `%c` in $var\n", \
			str[i]);
		return (true);
	}
	return (false);
}

void	get_var_name_in_accolade(char **var_name, char *str, int i)
{
	int	var_name_len;

	var_name_len = 0;
	while (str[i] && str[i] != '}')
	{
		if (unsuported_accolade_operator(str, i))
			return ;
		i++;
		var_name_len++;
	}
	if (var_name_len == 0)
		return ;
	*var_name = malloc(sizeof(char) * (var_name_len + 1));
	if (!(*var_name))
		return ;
	(*var_name)[var_name_len] = '\0';
	ft_strlcpy(*var_name, str + i - var_name_len, var_name_len + 1);
}
