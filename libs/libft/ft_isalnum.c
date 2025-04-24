/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laufarin <laufarin@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 15:21:41 by laufarin          #+#    #+#             */
/*   Updated: 2023/09/25 02:21:17 by laufarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_isalnum(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
		|| (c >= '0' && c <= '9'))
	{
		return (1);
	}
	return (0);
}
/*int	main(void)
{
	int	is_alnum;
	int	a;

	a = '}';
	is_alnum = ft_isalnum(a);
	if (is_alnum == 0)
	{
		printf("No valido\n");
	}
	else
	{
		printf("Correcto\n");
	}
	return (0);
}*/
