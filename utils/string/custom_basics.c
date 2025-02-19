/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_basics.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 16:13:36 by ofilloux          #+#    #+#             */
/*   Updated: 2025/02/19 16:37:42 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

//join string with specific char and free the sources
char	*c_strjoin(char *s1, char *s2, char c)
{
	char	*ptr;
	int		i;
	int		j;

	i = 0;
	j = 0;
	ptr = malloc(sizeof(char) * (s_len(s1) + (s_len(s2) + 2)));
	if (ptr == NULL)
		return (NULL);
	while (s1[i])
	{
		ptr[i] = s1[i];
		i++;
	}
	ptr[i] = c;
	while (s2[j])
	{
		ptr[i + 1 + j] = s2[j];
		j++;
	}
	ptr[i + 1 + j] = '\0';
	free (s1);
	free (s2);
	return (ptr);
}

// cc ./utils/string/custom_basics.c ./utils/string/quotes.c ./utils/string/basics.c -lreadline -g -o test
// valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=readline.supp -s ./test
// int main()
// {
// 	char	*line;
// 	int		i = 0;

// 	line = NULL;
// 	while (true )
// 	{
// 		line = readline("minishell> ");
// 		while (line && !all_quote_closed(line))
// 		{

// 			line = c_strjoin(line, readline("dquote> "), '\n');
// 			printf("line = -%s-\n", line);
// 		}
// 		break ;
// 	}
// 	if (line)
// 		free(line);
// 	return (0);

// }
