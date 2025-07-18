/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expension_root.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 17:29:54 by ofilloux          #+#    #+#             */
/*   Updated: 2025/07/11 17:44:16 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

/* char	**retokenize_after_exp(char	***chunk)
{
	int	i;

	i = 0;
	while (*chunk[i])
	{

		i++;
	}
} */

static int	calc_total_len(char **argv)
{
	int		i;
	int		total_len;

	i = 0;
	total_len = 0;
	while (argv[i])
	{
		if (argv[i] && argv[i][0])
			total_len += ft_strlen(argv[i]);
		if (argv[i + 1])
			total_len += 1;
		i++;
	}
	return (total_len);
}

static void	copy_with_sep(char **argv, char sep, char *result)
{
	int	i;
	int	offset;
	int	j;

	i = 0;
	offset = 0;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
			result[offset++] = argv[i][j++];
		if (argv[i] && argv[i + 1])
			result[offset++] = sep;
		i++;
	}
	result[offset] = '\0';
}

char	*concat_substrs_sep(char **argv, char sep)
{
	int		total_len;
	char	*result;

	if (!argv)
		return (NULL);
	total_len = calc_total_len(argv);
	result = malloc(total_len + 1);
	if (!result)
		return (NULL);
	copy_with_sep(argv, sep, result);
	return (result);
}

/**
* @brief : duplicate a segmented substring, in a char **; and expend the tockens
* from a start point included to a end point included.
*
*	@note chunk malloc :
*    end - start +1 to include the starst and the end ;  +1 for the null
*/
char	**expension_root(t_data *data, char **substring_arr, int start, int end)
{
	char	**chunk;
	int		i;
	int		j;

	i = start;
	j = 0;
	chunk = NULL;
	chunk = malloc(sizeof(char *) * (end - start + 1 + 1));
	if (!chunk)
		return (NULL);
	while (i <= end)
	{
		chunk[j] = expend_token(data, substring_arr[i]);
		if (NULL == chunk[j])
			return (free_uncomplete_av(&chunk, j));
		i++;
		j++;
	}
	chunk[j] = NULL;
	return (chunk);
}

void	retocken_after_expension(char ***chunk_tokens)
{
	char	**tmp;
	char	*tmp2;

	tmp = *chunk_tokens;
	tmp2 = concat_substrs_sep(*chunk_tokens, ' ');
	*chunk_tokens = split_quoted(tmp2, ' ');
	ft_free((void **) &tmp2);
	free_av(&tmp);
}
