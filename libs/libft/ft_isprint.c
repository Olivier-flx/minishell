/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laufarin <laufarin@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 20:47:52 by laufarin          #+#    #+#             */
/*   Updated: 2023/09/05 21:17:14 by laufarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
	{
		return (1);
	}
	return (0);
}

/*
int	main(void)
{
	int	is_print;
	int	p;
	
	p = 128;
	is_print = ft_isprint(p);

	if (is_print == 0)
	{
		printf("No es correcto\n");
	}
	else
	{
		printf("Vamos bien\n");
	}
	return (0);
}
*/
