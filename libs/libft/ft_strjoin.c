/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laufarin <laufarin@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 17:53:42 by laufarin          #+#    #+#             */
/*   Updated: 2023/09/25 01:33:36 by laufarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ptr;
	char	*cpy_1;
	char	*cpy_2;
	int		i;
	int		j;

	i = 0;
	j = 0;
	cpy_1 = (char *) s1;
	cpy_2 = (char *) s2;
	ptr = malloc(sizeof(char) * (ft_strlen(s1) + (ft_strlen(s2) +1)));
	if (ptr == NULL)
		return (NULL);
	while (cpy_1[i])
	{
		ptr[i] = cpy_1[i];
		i++;
	}
	while (cpy_2[j])
	{
		ptr[i + j] = cpy_2[j];
		j++;
	}
	ptr[i + j] = '\0';
	return (ptr);
}
