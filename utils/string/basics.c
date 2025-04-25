/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basics.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 12:33:41 by marvin            #+#    #+#             */
/*   Updated: 2025/04/25 12:33:41 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

char    *ft_strjoin3(char *s1, char *s2, char *s3)
{
    char    *tmp;
    char    *result;

    tmp = ft_strjoin(s1, s2);
    result = ft_strjoin(tmp, s3);
    free(tmp);
    return(result);

}