/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 15:37:35 by laufarin          #+#    #+#             */
/*   Updated: 2025/02/07 16:36:15 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

	//unsigned int	i;
void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char			*pdst;
	char			*psrc;

	pdst = (char *)dst;
	psrc = (char *)src;
	if (psrc == NULL && pdst == NULL)
		return (NULL);
	if (dst > src)
	{
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
//		i = 0;
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
