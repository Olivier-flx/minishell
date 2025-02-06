/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laufarin <laufarin@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 18:09:22 by laufarin          #+#    #+#             */
/*   Updated: 2023/09/25 01:57:11 by laufarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	contar_palabras(const char *s, char c)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			count++;
		i++;
	}
	return (count);
}

static char	**free_matrix(char **matrix, int col)
{
	int	i;

	i = 0;
	while (i < col)
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**matrix;
	int		i;
	int		j;
	int		start;

	i = 0;
	j = 0;
	start = 0;
	matrix = malloc(sizeof(char *) * (contar_palabras(s, c) + 1));
	if (matrix == NULL)
		return (NULL);
	while (s[i])
	{
		if (i > 0 && s[i] != c && s[i - 1] == c)
			start = i;
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
		{
			matrix[j++] = ft_substr(s, start, i - start + 1);
			if (!matrix[j - 1])
				return (free_matrix(matrix, j - 1));
		}
		i++;
	}
	matrix[j] = NULL;
	return (matrix);
}
/*int main()
{
	char **splitted;
	splitted = ft_split("hola    que tal", ' ');
	int i;
	i = 0;
	while(splitted[i])
	{
		printf("%s\n", splitted[i]);
		i++;
	}
	return 0;
}*/
