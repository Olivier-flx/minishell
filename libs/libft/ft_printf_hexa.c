/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_hexa.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laufarin <laufarin@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 18:51:31 by laufarin          #+#    #+#             */
/*   Updated: 2024/06/07 13:35:02 by laufarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf_hexa(unsigned int nb)
{
	int	i;
	int	ret;

	i = 0;
	if (nb >= 16)
	{
		ret = ft_printf_hexa(nb / 16);
		if (ret == -1)
			return (-1);
		i += ret;
		if (ft_printf_char(BASE_MAYUS[nb % 16]) == -1)
			return (-1);
		i++;
	}
	if (nb < 16)
	{
		i++;
		if (ft_printf_char(BASE_MAYUS[nb]) == -1)
			return (-1);
	}
	return (i);
}
