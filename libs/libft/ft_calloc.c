/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laufarin <laufarin@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 16:08:53 by laufarin          #+#    #+#             */
/*   Updated: 2023/09/25 00:21:07 by laufarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char			*ptr;
	unsigned int	i;

	i = 0;
	ptr = malloc (count * size);
	if (ptr == NULL)
	{
		return (NULL);
	}
	while (i < (count * size))
	{
		ptr[i] = '\0';
		i++;
	}
	return (ptr);
}
/*
int main (void)
{
	
	char *ptr;
	ptr = ft_calloc(8, sizeof(char));
	if(ptr == NULL)
	{
		printf("El malloc a fallado!!!!");
		return 0;
	}
	printf("Esta caracter deberia ser null |%c|\n", ptr[3]);
}*/
