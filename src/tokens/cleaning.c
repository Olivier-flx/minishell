/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 18:48:17 by ofilloux          #+#    #+#             */
/*   Updated: 2025/02/17 15:12:28 by ofilloux         ###   ########.fr       */
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

void	generate_trimed_str(char **new_string, char *src, int ns_len)
{
	int	i;
	int	j;
	int	spc_flg;

	i = 0;
	j = 0;
	spc_flg = 0;
	while (src && src[i] && (src[i] == ' ' || src[i] == '\t' || src[i] == '\n'))
		i++;
	while (src && src[i] && j < ns_len)
	{
		if (spc_flg == 0 && (src[i] == ' ' || src[i] == '\t' || src[i] == '\n'))
		{
			spc_flg = 1;
			(*new_string)[j++] = src[i++];
		}
		else if (spc_flg == 1 && (src[i] == ' ' || src[i] == '\t' \
				|| src[i] == '\n'))
			i++;
		else
		{
			spc_flg = 0;
			(*new_string)[j++] = src[i++];
		}
		// i++;
	}
	(*new_string)[ns_len] = '\0';
}

char	*ft_trim(char *src, bool is_malloced)
{
	// int		i;
	char	*new_string;
	int		dbl_spaces;
	int		src_len;

	dbl_spaces = count_useless_spaces(src);
	src_len = s_len(src);
	new_string = malloc ((src_len - dbl_spaces + 1) * sizeof(char));
	if (!new_string)
		return (NULL);
	generate_trimed_str(&new_string, src, src_len - dbl_spaces);
	//TO CONTINUE

	if (is_malloced)
		free(src);
	return (new_string);
}

// cc ./src/tokens/cleaning.c ./utils/string/basics.c -g -o test
// int main()
// {
// 	char	*new_string;

// 	new_string = ft_trim(" le  monde ", false);
// 	printf("valeur : `%s`\n", new_string);
// 	free(new_string);
// 	return (0);
// }
