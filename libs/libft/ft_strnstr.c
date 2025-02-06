/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laufarin <laufarin@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 17:32:29 by laufarin          #+#    #+#             */
/*   Updated: 2023/09/25 02:14:30 by laufarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!needle[i])
		return ((char *)haystack);
	while (needle[i] && haystack[j] && i < len)
	{
		if (haystack[j] == needle[0])
		{
			while (haystack[j + i] == needle[i] && haystack[i + j] && \
					needle[i] && i + j < len)
				i++;
			if (!needle[i])
				return ((char *) haystack + j);
		}
		j++;
		i = 0;
	}
	return (0);
}
/*
int	main(void)
{
	char	*a;
	char	*b;
	char	*ptr;

	a = "El gato estaba en el tejado";
	b = "gato";
	
	ptr = ft_strnstr(a, b, 3);

	printf("%s\n", ptr);
	return (0);
}*/
