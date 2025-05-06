/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_from_substring_arr.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 17:29:54 by ofilloux          #+#    #+#             */
/*   Updated: 2025/05/06 11:43:59 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

/* char	**retokenize_after_exp(char	***chunk)
{
	int	i;

	i = 0;
	while (*chunk[i])
	{

		i++;
	}
} */


// @info : duplicate a segmented substring, in a char **;
// from a start point included to a end point included.
char	**dup_pp_char(t_data *data, char **substring_arr, int start, int end)
{
	char	**chunk;
	// char	**tmp;
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
	//tmp = chunk;
	//chunk = retokenize_after_exp(chunk);
	//free_av(tmp);
	return (chunk);
}
