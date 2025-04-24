/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_unsigned_numbers.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laufarin <laufarin@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 21:16:19 by laufarin          #+#    #+#             */
/*   Updated: 2024/06/07 13:37:39 by laufarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_unum_size(unsigned int n)
{
	int	count;

	count = 0;
	if (n == 0)
		return (1);
	while (n)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

int	ft_unsigned_itoa(unsigned int n)
{
	char	storage[11];
	int		size;
	int		count;

	count = 0;
	size = ft_unum_size(n);
	storage[size] = '\0';
	while (n != 0)
	{
		storage[size - 1] = (n % 10) + '0';
		n = n / 10;
		size--;
	}
	while (storage[count])
	{
		if (write (1, &storage[count], 1) == -1)
			return (-1);
		count++;
	}
	return (count);
}

int	ft_unsigned(unsigned int n)
{
	if (n == 0)
		return (write(1, "0", 1));
	return (ft_unsigned_itoa(n));
}
