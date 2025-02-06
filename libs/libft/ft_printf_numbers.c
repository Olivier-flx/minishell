/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_numbers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laufarin <laufarin@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 17:53:00 by laufarin          #+#    #+#             */
/*   Updated: 2024/06/07 13:36:15 by laufarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	count_number_size(int num)
{
	int	count;

	count = 0;
	if (num == 0)
		return (1);
	if (num < 0)
		count = 1;
	while (num != 0)
	{
		num = num / 10;
		count++;
	}
	return (count);
}

int	ft_printf_numbers_itoa(int num)
{
	char	storage[12];
	int		num_size;
	int		count;

	num_size = count_number_size(num);
	storage[num_size] = '\0';
	if (num < 0)
	{
		storage[0] = '-';
		num = num * -1;
	}
	while (num != 0)
	{
		storage[num_size - 1] = (num % 10) + '0';
		num = num / 10;
		num_size--;
	}
	count = 0;
	while (storage[count])
	{
		if (write(1, &storage[count], 1) == -1)
			return (-1);
		count++;
	}
	return (count);
}

int	ft_printf_numbers(int num)
{
	if (num == 0)
		return (write(1, "0", 1));
	if (num == -2147483648)
		return (write(1, "-2147483648", 11));
	return (ft_printf_numbers_itoa(num));
}
