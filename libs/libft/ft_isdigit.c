/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laufarin <laufarin@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 22:40:07 by laufarin          #+#    #+#             */
/*   Updated: 2023/09/05 20:01:36 by laufarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
	{
		return (1);
	}
	return (0);
}
/*int	main(void)
{
	int	is_digit;
	int	d;

	d = '3';
	is_digit = ft_isdigit(d);
	if (is_digit == 0)
	{
		printf("no es un digito\n");
	}
	else
	{
		printf("es un digito\n");
	}
	return (0);
}*/
