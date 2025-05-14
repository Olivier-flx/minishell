/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 17:37:48 by ofilloux          #+#    #+#             */
/*   Updated: 2025/05/14 16:40:54 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

// return the number of operator present in src
int	count_operador_from_pp_char(char **content)
{
	int		i;
	int		k;
	t_quote	quote;

	i = 0;
	k = 0;
	init_quotes(&quote);
	while (content[i])
	{
		if (is_operator(content[i], 0, &quote) > 0) //Modifier apres
			k++;
		i++;
	}
	return (k);
}

// return the number of operator present in src
int	count_redir_from_pp_char(char **content)
{
	int		i;
	int		k;
	t_quote	quote;

	i = 0;
	k = 0;
	init_quotes(&quote);
	while (content[i])
	{
		if (is_redirection(content[i], 0, &quote) > 0)
			k++;
		i++;
	}
	return (k);
}

int	count_input_redir_from_pp_char(char **content)
{
	int		i;
	int		k;
	t_quote	quote;

	i = 0;
	k = 0;
	init_quotes(&quote);
	while (content[i])
	{
		if (is_input_redir(content[i], 0, &quote) > 0)
			k++;
		i++;
	}
	return (k);
}

bool	has_heredoc_from_pp_char(char **content)
{
	int		i;
	t_quote	quote;

	i = 0;
	init_quotes(&quote);
	while (content[i])
	{
		if (is_input_redir(content[i], 0, &quote) == 2)
			return (true);
		i++;
	}
	return (false);
}
