/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laufarin <laufarin@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 19:45:29 by laufarin          #+#    #+#             */
/*   Updated: 2023/09/05 20:29:38 by laufarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
	{
		return (1);
	}
	return (0);
}
/*
int	main(void)
{
	int	is_ascii;
	int	a;

	a = 210;
	is_ascii = ft_isascii(a);
	
		if (is_ascii == 0)
	{
		printf ("No es correcto\n");
	}
		else
		{
			printf ("Muy bien de momento\n");
		}
	return (0);
}*/
