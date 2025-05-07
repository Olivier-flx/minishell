/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_files_in_chunks.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 17:28:17 by ofilloux          #+#    #+#             */
/*   Updated: 2025/05/07 15:36:10 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	count_redir_files_in_chunks(char **content)
{
	int		i;
	int		k;
	t_quote	quote;

	init_quotes(&quote);
	i = 0;
	k = 0;
	while (content[i])
	{
		if (is_redirection(content[i], 0, &quote) > 0)
		{
			if(content[i + 1] && !is_operator(content[i + 1], 0, &quote))
				k++;
		}
		i++;
	}
	return (k);
}

/// @brief  In case of << the file name is the heredoc delimiter
/// @param content
/// @return number of input file
int	count_input_files_in_chunks(char **content)
{
	int		i;
	int		k;
	t_quote	quote;

	init_quotes(&quote);
	i = 0;
	k = 0;
	while (content[i])
	{
		if (is_input_redir(content[i], 0, &quote) > 0)
		{
			if(content[i + 1] && !is_operator(content[i + 1], 0, &quote))
				k++;
		}
		i++;
	}
	return (k);
}

