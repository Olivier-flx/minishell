/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basics.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 10:05:22 by ofilloux          #+#    #+#             */
/*   Updated: 2025/01/26 10:05:33 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	s_len(const char *s)
{
	int	i;

	if (s == NULL)
		return (0);
	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*s_dup(char *s)
{
		char	*cpy;
		int	 i = 0;

		if(!s)
				return (NULL);
		cpy = malloc((s_len(s) + 1) * sizeof(char));
		if (!cpy)
				return (NULL);
		while(s[i])
		{
				cpy[i] = s[i];
				i++;
		}
		cpy[i] = '\0';
		return (cpy);
}
