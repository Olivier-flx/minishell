/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laufarin <laufarin@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 17:50:48 by laufarin          #+#    #+#             */
/*   Updated: 2023/09/25 01:49:20 by laufarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = 0;
	while (dst[len] != '\0')
	{
		len++;
	}
	if (dstsize < len || dstsize == 0)
		return (dstsize + ft_strlen(src));
	while (src[i] != '\0' && len + i < dstsize - 1)
	{
		dst[len + i] = src[i];
		i++;
	}
	dst[len + i] = '\0';
	return (len + i + ft_strlen(&src[i]));
}

/*
int	main(void)
{
char destino[50];
char destino2[50];
 ft_strlcat(destino, "123", 0);
 strlcat(destino2, "123", 0);
 printf("%s\n", destino);
 printf("%s\n", destino2);

 return 0;
}
*/
