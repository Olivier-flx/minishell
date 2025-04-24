/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 19:06:10 by marvin            #+#    #+#             */
/*   Updated: 2025/04/21 19:06:10 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char    *ft_strjoin3(char const*s1, char const*s2, char const*s3)
{
    char    *tmp;
    char    *result;

    tmp = ft_strjoin(s1, s2);
    result = ft_strjoin(tmp, s3);
    free(tmp);
    return(result);

}