/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_hexamin.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laufarin <laufarin@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 17:31:47 by laufarin          #+#    #+#             */
/*   Updated: 2024/06/07 13:35:46 by laufarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf_hexamin(unsigned int nb)
{
	int		i;
	int		ret;

	i = 0;
	if (nb >= 16)
	{
		ret = ft_printf_hexamin(nb / 16);
		if (ret == -1)
			return (-1);
		i += ret;
		if (ft_printf_char(BASE_MIN[nb % 16]) == -1)
			return (-1);
		i++;
	}
	if (nb < 16)
	{
		i++;
		if (ft_printf_char(BASE_MIN[nb]) == -1)
			return (-1);
	}
	return (i);
}
