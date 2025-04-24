/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_operators.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 11:30:14 by ofilloux          #+#    #+#             */
/*   Updated: 2025/04/22 11:36:44 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

// ignore <> that is working in bash
static int check_tokens(t_chunk *chunk)
{
	int		flag;
	char	*tmp;
	int		i;
	t_quote	quotes;

	init_quotes(&quotes);
	flag = 0;
	tmp = NULL;
	i = 0;
	while (chunk && chunk->tokens && chunk->tokens[i])
	{
		if (0 == flag && (is_operator(chunk->tokens[i], 0, &quotes) || chunk->tokens[i][0] == '|'))
		{
			tmp = chunk->tokens[i++];
			flag = 1;
			continue ;
		}
		if (1 == flag && tmp && tmp[0] == '<' && chunk->tokens[i][0] == '>')
			flag = 0;
			//return(printf("bash: syntax error near unexpected token `>'\n"));
		if (1 == flag && chunk->tokens[i][0] =='>')
			return(printf("bash: syntax error near unexpected token `>'\n"));
		if (1 == flag && chunk->tokens[i][0] =='<')
			return(printf("bash: syntax error near unexpected token `<'\n"));
		flag = 0;
		i++;
	}
	return (SUCCESS);
}

// check for >>> or <<< or << < or >> > or < << or > >>
// or ><
// Check for error in every nodes tokens
int	check_for_triple(t_dlist **cmd_list)
{
	t_dlist	*i_node;

	i_node = *cmd_list;
	while(i_node)
	{
		if (check_tokens((t_chunk *)i_node->content) > 0)
			return (ERROR);
		i_node = i_node->next;
	}
	return(SUCCESS);
}
