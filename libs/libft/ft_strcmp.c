/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laufarin <laufarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 14:09:29 by laufarin          #+#    #+#             */
/*   Updated: 2025/03/31 14:20:20 by laufarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned char	*ptr1;
	unsigned char	*ptr2;
	int				i;

	ptr1 = (unsigned char *)s1;
	ptr2 = (unsigned char *)s2;
	i = 0;
	while (!(ptr1[i] == '\0' && ptr2[i] == '\0'))
	{
		if (ptr1[i] != ptr2[i])
			return (ptr1[i] - ptr2[i]);
		i++;
	}
	return (0);
}
/*
#include <stdio.h>

int ft_strcmp(const char *s1, const char *s2);

int main(void)
{
    char *str1 = "hola";
    char *str2 = "hola";
    char *str3 = "holb";
    char *str4 = "hol";

    printf("Comparando '%s' y '%s': %d\n", str1, str2, ft_strcmp(str1, str2)); // 0
    printf("Comparando '%s' y '%s': %d\n", str1, str3, ft_strcmp(str1, str3)); // negativo
    printf("Comparando '%s' y '%s': %d\n", str1, str4, ft_strcmp(str1, str4)); // positivo

    return 0;
}
*/
