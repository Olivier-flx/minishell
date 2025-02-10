/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laufarin <laufarin@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 13:37:02 by laufarin          #+#    #+#             */
/*   Updated: 2023/09/25 02:01:09 by laufarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	calc_malloc_len(char const *s, unsigned int start, size_t len)
{
	if (start > ft_strlen(s))
		len = 0;
	if (ft_strlen(s) - start < len)
		len = ft_strlen(s) - start;
	return (len);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	unsigned int	j;
	char			*ptr;

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
