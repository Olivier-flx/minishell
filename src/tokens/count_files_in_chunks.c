/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_files_in_chunks.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 17:28:17 by ofilloux          #+#    #+#             */
/*   Updated: 2025/04/30 21:46:26 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	count_files_in_chunks(char **content)
{
	int		i;
	int		k;
	t_quote	quote;

	init_quotes(&quote);
	i = 0;
	k = 0;
	while (content[i])
	{
		if (is_operator(content[i], 0, &quote) > 0)
		{
			if(content[i + 1] && !is_operator(content[i + 1], 0, &quote))
				k++;
		}
		i++;
	}
	return (k);
}
