/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_pointer.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laufarin <laufarin@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 17:31:47 by laufarin          #+#    #+#             */
/*   Updated: 2024/06/07 13:36:44 by laufarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf_pointer_recursive(unsigned long nb)
{
	int		i;
	int		ret;

	i = 0;
	if (nb >= 16)
	{
		ret = ft_printf_pointer_recursive(nb / 16);
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

int	ft_printf_pointer(unsigned long nb)
{
	int	len;

	if (write(1, "0x", 2) == -1)
		return (-1);
	len = ft_printf_pointer_recursive(nb);
	if (len == -1)
		return (-1);
	len = len + 2;
	return (len);
}
