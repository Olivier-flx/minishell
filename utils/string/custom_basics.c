/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_basics.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 16:13:36 by ofilloux          #+#    #+#             */
/*   Updated: 2025/05/14 10:27:24 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"


char	*strjoin_and_free(char *s1, char *s2)
{
	char	*ptr;
	int		i;
	int		j;

	i = 0;
	j = 0;
	ptr = malloc(sizeof(char) * (ft_strlen(s1) + (ft_strlen(s2) + 1)));
	if (ptr == NULL)
		return (NULL);
	while (s1 && s1[i])
	{
		ptr[i] = s1[i];
		i++;
	}
	while (s2 && s2[j])
	{
		ptr[i + j] = s2[j];
		j++;
	}
	ptr[i + j] = '\0';
	ft_free ((void **) &s1);
	ft_free ((void **) &s2);
	return (ptr);
}


/**
 * @brief Joins two strings with a specific character and frees the source strings.
 *
 * Concatenates `s1` and `s2` with `c` in between, allocates memory for the result,
 * and frees the original strings.
 *
 * @param s1 The first string to join.
 * @param s2 The second string to join.
 * @param c The character to insert between the strings.
 * @return (char *) The newly allocated concatenated string, or NULL if allocation fails.
 *
 * @note The caller must free the returned string.
 * @see ft_strlen
 */
char	*c_strjoin(char *s1, char *s2, char c)
{
	char	*ptr;
	int		i;
	int		j;

	i = 0;
	j = 0;
	ptr = malloc(sizeof(char) * (ft_strlen(s1) + (ft_strlen(s2) + 2)));
	if (ptr == NULL)
		return (NULL);
	while (s1 && s1[i])
	{
		ptr[i] = s1[i];
		i++;
	}
	ptr[i] = c;
	while (s2 && s2[j])
	{
		ptr[i + 1 + j] = s2[j];
		j++;
	}
	ptr[i + 1 + j] = '\0';
	ft_free ((void **) &s1);
	ft_free ((void **) &s2);
	return (ptr);
}

static size_t	calc_malloc_len(char const *s, unsigned int start, size_t len)
{
	if (start > ft_strlen(s))
		len = 0;
	if (ft_strlen(s) - start < len)
		len = ft_strlen(s) - start;
	return (len);
}

//substring a string between a start point  en a end point
char	*c_ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	unsigned int	j;
	char			*ptr;

	if(len <= 0 || start >= (unsigned int) ft_strlen(s))
		return (NULL);
	i = 0;
	j = 0;
	len = calc_malloc_len(s, start, len);
	ptr = malloc(sizeof(char) * len + 1);
	if (ptr == NULL)
		return (NULL);
	while (s[i])
	{
		if (start == i)
		{
			while (j < len)
			{
				ptr[j] = s[i + j];
				j++;
			}
		}
		i++;
	}
	ptr[j] = '\0';
	return (ptr);
}

// cc ./utils/string/custom_basics.c ./utils/string/quotes.c ./utils/string/basics.c -lreadline -g -o test
// valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=readline.supp -s ./test
// int main()
// {
// 	char	*line;
// 	int		i = 0;

// 	line = NULL;
// 	while (true )
// 	{
// 		line = readline("minishell> ");
// 		while (line && !tocken_quote_closed(line))
// 		{

// 			line = c_strjoin(line, readline("dquote> "), '\n');
// 			printf("line = -%s-\n", line);
// 		}
// 		break ;
// 	}
// 	if (line)
// 		free(line);
// 	return (0);

// }
