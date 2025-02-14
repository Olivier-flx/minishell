/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 18:48:17 by ofilloux          #+#    #+#             */
/*   Updated: 2025/02/14 19:37:01 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"
#include <stdio.h>

static int	count_r_useless_spc(char *src, int i)
{
	int	spc_flg;
	int	k;

	k = 0;
	spc_flg = 0;
	i--;
	while (src && i >= 0 && (src[i] == ' ' || src[i] == '\t' || src[i] == '\n'))
	{
		i--;
		k++;
	}
	if (k >= 1)
		return (1);
	else
		return (0);
}


int	count_useless_spaces(char *src)
{
	int	i;
	int	spc_flg;
	int	k;

	i = 0;
	spc_flg = 0;
	while (src && src[i] && (src[i] == ' ' || src[i] == '\t' || src[i] == '\n'))
		i++;
	k = i;
	while (src && src[i])
	{
		if (spc_flg == 0 && (src[i] == ' ' || src[i] == '\t' || src[i] == '\n'))
			spc_flg = 1;
		else if (spc_flg == 1 && (src[i] == ' ' || src[i] == '\t' \
				|| src[i] == '\n'))
			k++;
		else
			spc_flg = 0;
		i++;
	}
	k += count_r_useless_spc(src, i);
	return (k);
}

char	*ft_trim(char *src, bool is_malloced)
{
	int		i;
	char	*new_string;
	int		dbl_spaces;

	dbl_spaces = count_useless_spaces(src);

	//TO CONTINUE

	if (is_malloced)
		free(src);
	return (new_string);
}


// int main()
// {
// 	return (printf("valeur : %i\n",count_useless_spaces(" le  monde ")));
// }
