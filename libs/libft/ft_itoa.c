/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laufarin <laufarin@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 17:13:05 by laufarin          #+#    #+#             */
/*   Updated: 2023/09/25 03:14:04 by laufarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_len(int n)
{
	int	len;

	len = 0;
	if (n <= 0)
		len = 1;
	while (n != 0)
	{
		len++;
		n = n / 10;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*ptr;
	int		len;
	int		sign;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	len = ft_len(n);
	sign = -1;
	ptr = (char *)malloc(sizeof (char) * (len + 1));
	if (!ptr)
		return (NULL);
	ptr[len] = '\0';
	if (n == 0)
		ptr[0] = '0';
	if (n < 0)
	{
		ptr[0] = '-';
		n = n * -1;
	}
	while (n > 0)
	{
		ptr[--len] = '0' + (n % 10);
		n = n / 10;
	}
	return (ptr);
}
/*
#include <stdio.h>
#include <string.h>
int main() 
{
   	int	num = 12345;
    char	*str = ft_itoa(num);

    if (str != NULL) {
        printf("Número: %s\n", str);
        free(str); // Libera la memoria después de su uso
    } else {
        printf("No se pudo asignar memoria.\n");
    }

    return 0;
}*/
