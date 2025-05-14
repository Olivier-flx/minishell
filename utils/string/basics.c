/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basics.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 12:33:41 by marvin            #+#    #+#             */
/*   Updated: 2025/05/14 10:41:56 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

char	*ft_strjoin3(char *s1, char *s2, char *s3)
{
	char	*tmp;
	char	*result;

	tmp = ft_strjoin(s1, s2);
	result = ft_strjoin(tmp, s3);
	free(tmp);
	return(result);
}

bool	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\r');
}

bool	line_is_only_spaces(char *line)
{
	int	i;

	i = -1;
	if (!line)
		return true;
	while (line[++i])
	{
		if (!ft_isspace(line[i]))
			return false;
	}
	return true;
}
