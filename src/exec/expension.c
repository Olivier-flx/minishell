/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expension.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 17:38:16 by ofilloux          #+#    #+#             */
/*   Updated: 2025/04/28 18:55:17 by ofilloux         ###   ########.fr       */
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

char	*expend(char *str)
{
	char	*ret_val;
	int		i;
	t_quote	quotes;

	i = 0;
	init_quotes(&quotes);
	while (str[i])
	{
		quote_increment(str, i, &quotes);
		if(quotes.dbl_quote % 2 == 1 && str[i] == '$')
			i += get_var_name(str, i);
	}


}
