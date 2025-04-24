/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laufarin <laufarin@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 20:33:20 by laufarin          #+#    #+#             */
/*   Updated: 2023/09/13 17:56:19 by laufarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*ptr;

	ptr = (unsigned char *)b;
	i = 0;
	while (i < len)
	{
		ptr[i] = c;
		i++;
	}
	return (b);
}
/*
int	main(void)
{
	void *b;
	unsigned char *ptr;

	b = (void *)malloc(sizeof(char) * 30);
	ptr = ft_memset(b, 'b', 4);
	ptr[4] = '\0';
	printf("tengo en b |%s|", ptr);

}*/
