/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_from_substring_arr.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 17:29:54 by ofilloux          #+#    #+#             */
/*   Updated: 2025/03/19 18:27:18 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

char	**dup_pp_char(char **substring_arr, int start, int end)
{
	char	**chunk;
	int		i;
	int		j;

	i = start;
	j = 0;
	chunk = NULL;
	chunk = malloc(sizeof(char *) * (end - start + 1));
	if (!chunk)
		return (NULL);
	while (i <= end)
	{
		chunk[j] = s_dup(substring_arr[i]);
		if (NULL == chunk[j])
			return (free_uncomplete_av(chunk, j));
		i++;
		j++;
	}
	chunk[j] = 0;
	return (chunk);
}
