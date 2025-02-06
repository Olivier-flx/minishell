/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laufarin <laufarin@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 13:01:50 by laufarin          #+#    #+#             */
/*   Updated: 2023/09/25 00:36:11 by laufarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = ft_strlen(s);
	c = (unsigned char) c;
	while (i >= 0 && s)
	{
		if (s[i] == c)
			return ((char *)&s[i]);
		i--;
	}
	return (0);
}
/*
int	main(void)
{
	const char	*a;
	int	b;

	a = "probando";
	b = 'r';
	ft_strrchr(a,b);

	printf("%s\n", ft_strrchr(a, b));
	return (0);
}*/
