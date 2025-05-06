/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_from_substring_arr.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 17:29:54 by ofilloux          #+#    #+#             */
/*   Updated: 2025/05/06 10:16:41 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

// @info : duplicate a segmented substring, in a char **;
// from a start point included to a end point included.
char	**dup_pp_char(t_data *data, char **substring_arr, int start, int end)
{
	char	**chunk;
	int		i;
	int		j;

	i = start;
	j = 0;
	chunk = NULL;
	chunk = malloc(sizeof(char *) * (end - start + 1 + 1)); //@info end - start +1 to include the starst and the end ;  +1 for the null
	if (!chunk)
		return (NULL);
	while (i <= end)
	{
		chunk[j] = expend_token(data, substring_arr[i]);
		if (NULL == chunk[j])
			return (free_uncomplete_av(chunk, j));
		i++;
		j++;
	}
	chunk[j] = NULL;
	return (chunk);
}
