/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laufarin <laufarin@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 18:45:51 by laufarin          #+#    #+#             */
/*   Updated: 2023/09/25 01:54:14 by laufarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_space(char c)
{
	while (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r')
	{
		return (1);
	}
	return (0);
}

//Paso 1: Resultado empieza en 0
//Paso 2: Me como los espacios
//Paso 3: Cogemos el signo (1 si positivo, -1 si negativo)
//Paso 4: HAcer linea magica mientras str[i] >= '0' && str[i] <= '9'
//Paso 5: Devolvemos resultado * signo
int	ft_atoi(const char *str)
{
	int	resultado;
	int	i;
	int	sign;

	sign = 1;
	i = 0;
	resultado = 0;
	while (is_space(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		resultado = resultado * 10 + (str[i] - '0');
		i++;
	}
	return (resultado * sign);
}
/*
   int main()
   {
   printf("|%d|\n", ft_atoi("    110"));
   }
*/
