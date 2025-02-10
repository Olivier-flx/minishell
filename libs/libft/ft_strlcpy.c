/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laufarin <laufarin@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 18:11:48 by laufarin          #+#    #+#             */
/*   Updated: 2023/09/25 01:50:07 by laufarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <string.h>

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	unsigned int	l_src;
	unsigned int	i;

	l_src = 0;
	i = 0;
	while (src[l_src])
		l_src++;
	if (dstsize == 0)
		return (l_src);
	while ((i < dstsize -1) && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (l_src);
}
/*
int main()
{
	char *dst;
	char *dst2;

	dst = malloc(sizeof(char) * 10);
	dst2 = malloc(sizeof(char) * 10);
	memset(dst,'b', 9);
	memset(dst2,'b', 9);
	dst[9] = '\0';
	dst2[9] = '\0';
	printf("%s\n", dst);
	printf("%s\n", dst2);
	ft_strlcpy(dst, "hola que", 10);
	printf("%s\n", dst);
	strlcpy(dst2, "hola que", 10);
	printf("%s\n", dst2);
}*/
