/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laufarin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 19:43:07 by laufarin          #+#    #+#             */
/*   Updated: 2024/06/29 20:51:16 by laufarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	len_files(char **str)
{
	int	j;

	j = 0;
	while (str[j])
	{
		j++;
	}
	return (j);
}

char	**ft_realloc(char **str, char *s1)
{
	char	**tmp;
	int		len;

	tmp = 0;
	if (str == NULL)
	{
		tmp = malloc(sizeof (char) + 1);
		if (tmp == NULL)
			return (NULL);
		tmp[1] = NULL;
	}
	else
	{
		len = len_files(str);
		tmp = malloc(sizeof (char) * (len + 2));
		if (tmp == NULL)
			return (NULL);
		tmp[len + 1] = s1;
		tmp[len + 2] = NULL;
		free(str);
	}
	return (tmp);
}
