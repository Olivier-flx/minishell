/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laufarin <laufarin@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 15:37:35 by laufarin          #+#    #+#             */
/*   Updated: 2023/09/08 19:19:01 by laufarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char			*pdst;
	char			*psrc;
	unsigned int	i;

	pdst = (char *)dst;
	psrc = (char *)src;
	if (psrc == NULL && pdst == NULL)
		return (NULL);
	if (dst > src)
	{
		i = 0;
		while (len)
		{
			pdst[len -1] = psrc[len -1];
			len--;
		}
	}
	else
		ft_memcpy(pdst, psrc, len);
	return (dst);
}
/*
int main(void)
{
	char *a;
	char *b;

	a = malloc(sizeof(char) * 10);
	b = malloc(sizeof(char) * 10);
	a[0] = 'h';
	a[1] = 'o';
	a[2] = 'l';
	a[3] = 'a';
	a[4] = ' ';
	a[5] = 'c';
	a[6] = 'o';
	a[7] = 'm';
	a[8] = 'o';
	a[9] = '\0';
	b[5] = '\0';	
	ft_memmove(b,a,5);
	printf("En b ahors tengo |%s|\n", b);
}
*/
