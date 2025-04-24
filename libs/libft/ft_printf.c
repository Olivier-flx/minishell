/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laufarin <laufarin@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 21:13:10 by laufarin          #+#    #+#             */
/*   Updated: 2024/06/07 13:34:40 by laufarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf_char(char c)
{
	return (write(1, &c, 1));
}

int	eval_printf_var(char c, va_list args)
{
	int	count;

	count = 0;
	if (c == 'c')
		count = ft_printf_char(va_arg(args, int));
	else if (c == 's')
		count = ft_printf_strings(va_arg(args, char *));
	else if (c == '%')
		count = ft_printf_char('%');
	else if (c == 'd' || c == 'i')
		count = ft_printf_numbers(va_arg(args, int));
	else if (c == 'u')
		count = ft_unsigned(va_arg(args, unsigned int));
	else if (c == 'X')
		count = ft_printf_hexa(va_arg(args, unsigned int));
	else if (c == 'x')
		count = ft_printf_hexamin(va_arg(args, unsigned int));
	else if (c == 'p')
		count = ft_printf_pointer(va_arg(args, unsigned long));
	return (count);
}

int	ft_printf(const char *s, ...)
{
	int		i;
	int		count;
	int		ret;
	va_list	args;

	va_start(args, s);
	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '%')
		{
			i++;
			ret = eval_printf_var(s[i], args);
		}
		else
			ret = write (1, &s[i], 1);
		if (ret == -1)
			return (-1);
		count += ret;
		i++;
	}
	va_end(args);
	return (count);
}
/*
int main()
{
   int a;
   a = ft_printf("Hoy es puto |%u|\n", 1234);
   printf("El valor de retorno es: %d\n", a);

   int b;
   b = printf("Hoy es puto |%u|\n", 1234);
   printf("El valor de retorno es: %d\n", b);
}*/
