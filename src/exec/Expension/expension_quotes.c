/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expension_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 11:23:00 by ofilloux          #+#    #+#             */
/*   Updated: 2025/05/26 11:52:31 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

void	get_var_name_in_quotes(char **var_name, char *str, int i)
{
	int		var_name_len;
	t_quote	qts;

	var_name_len = 0;
	init_quotes(&qts);
	quote_increment(str, i++, &qts);
	while (str[i] && !quote_are_closed(&qts))
	{
		quote_increment(str, i, &qts);
		if (quote_are_closed(&qts))
			break ;
		if (unsuported_accolade_operator(str, i))
			return ;
		i++;
		var_name_len++;
	}
	if (var_name_len == 0)
		return;
	*var_name = malloc(sizeof(char) * (var_name_len + 1));
	if (!(*var_name))
		return ;
	(*var_name)[var_name_len] = '\0';
	ft_strlcpy(*var_name, str + i - var_name_len, var_name_len + 1);
}
