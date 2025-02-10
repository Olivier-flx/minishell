/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laufarin <laufarin@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 12:44:19 by laufarin          #+#    #+#             */
/*   Updated: 2023/09/22 15:27:58 by laufarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char			*is_src;
	char			*is_dst;
	unsigned int	i;

	is_src = (char *) src;
	is_dst = (char *) dst;
	if (is_src == NULL && is_dst == NULL)
		return (NULL);
	i = 0;
	while (i < n)
	{
		is_dst[i] = is_src[i];
		i++;
	}
	return (dst);
}
