/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_operators.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 11:30:14 by ofilloux          #+#    #+#             */
/*   Updated: 2025/06/23 17:18:59 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../header/minishell.h"

// ignore <> that is working in bash
/* static int check_tokens(t_chunk *chunk, t_quote *qts)
{
	int		flag;
	char	*tmp;
	int		i;

	flag = 0;
	tmp = NULL;
	i = -1;
	while (chunk && chunk->tokens && chunk->tokens[++i])
	{
		//printf("chunk->tokens[i] = %s\n", chunk->tokens[i]);// @debbug
		if (0 == flag && (is_operator(chunk->tokens[i], 0, qts)
			|| chunk->tokens[i][0] == '|'))
		{
			tmp = chunk->tokens[i];
			flag = 1;
			continue ;
		}
		if (1 == flag && tmp && tmp[0] == '<' && chunk->tokens[i][0] == '>')
			flag = 0;
		if (1 == flag && ft_strcmp(chunk->tokens[i], ">") == 0)
			return (printf("bash: syntax error near unexpected token `>'\n"));
		else if (1 == flag && ft_strcmp(chunk->tokens[i], "<") == 0)
			return (printf("bash: syntax error near unexpected token `<'\n"));
		else if (1 == flag && ft_strcmp(chunk->tokens[i], ">>") == 0)
			return (printf("bash: syntax error near unexpected token `>>'\n"));
		else if (1 == flag && ft_strcmp(chunk->tokens[i], "<<") == 0)
			return (printf("bash: syntax error near unexpected token `<<'\n"));
		flag = 0;
	}
	return (EXIT_SUCCESS);
} */

bool	is_operator_token(char *str)
{
	return (0 == ft_strcmp(str, ">>") \
			|| 0 == ft_strcmp(str, "<<") \
			|| 0 == ft_strcmp(str, ">") \
			|| 0 == ft_strcmp(str, "<"));
}

static int	check_invalid_sequences(char *current, char *previous, int flag)
{
	if (flag && previous && previous[0] == '<' && current[0] == '>')
		return (0);
	if (flag && ft_strcmp(current, ">") == 0)
		return (printf("bash: syntax error near unexpected token `>'\n"));
	if (flag && ft_strcmp(current, "<") == 0)
		return (printf("bash: syntax error near unexpected token `<'\n"));
	if (flag && ft_strcmp(current, ">>") == 0)
		return (printf("bash: syntax error near unexpected token `>>'\n"));
	if (flag && ft_strcmp(current, "<<") == 0)
		return (printf("bash: syntax error near unexpected token `<<'\n"));
	return (0);
}

static int	check_tokens(t_chunk *chunk, t_quote *qts)
{
	int		flag;
	char	*tmp;
	int		i;

	flag = 0;
	tmp = NULL;
	i = -1;
	while (chunk && chunk->tokens && chunk->tokens[++i])
	{
		if (!flag && (is_operator(chunk->tokens[i], 0, qts) \
			|| chunk->tokens[i][0] == '|'))
		{
			tmp = chunk->tokens[i];
			flag = 1;
			continue ;
		}
		if (check_invalid_sequences(chunk->tokens[i], tmp, flag))
			return (EXIT_FAILURE);
		flag = 0;
	}
	return (EXIT_SUCCESS);
}

// check for >>> or <<< or << < or >> > or < << or > >>
// or ><
// Check for error in every nodes tokens
int	check_for_triple(t_dlist **cmd_list)
{
	t_dlist	*i_node;
	t_quote	quotes;

	init_quotes(&quotes);
	i_node = *cmd_list;
	while (i_node)
	{
		if (check_tokens((t_chunk *)i_node->content, &quotes) > 0)
			return (EXIT_FAILURE);
		i_node = i_node->next;
	}
	return (EXIT_SUCCESS);
}
