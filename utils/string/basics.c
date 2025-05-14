/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basics.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 12:33:41 by marvin            #+#    #+#             */
/*   Updated: 2025/05/14 17:53:03 by ofilloux         ###   ########.fr       */
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
/*
//Retourne l'index de char c, ou -1 si pas trouvé
static int string_search(char *s, char c)
{
	int	i;

	i = 0;
	while (s && s[i])
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

//tronque en incluant l'index n
static char	*ft_truncate(char *s, int n)
{
	char	*cpy;
	int		i;
	int		s_len;

	i = 0;
	if (!s)
		return (NULL);
	s_len = (int) ft_strlen(s);
	if (n > s_len)
		n = s_len;
	cpy = malloc(sizeof(char) * (n + 2));
		return (NULL);
	while (i <= n)
	{
		cpy[i] = s[i];
		i++;
	}
	cpy[i] = '\0';
	return (cpy);
}
 */
