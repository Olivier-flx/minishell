/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   curly_bracket.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 16:50:22 by ofilloux          #+#    #+#             */
/*   Updated: 2025/06/23 16:54:38 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../header/minishell.h"

int	line_accolade_closed(char *line)
{
	int		i;
	t_quote	quotes;
	int		flag_acc;
	int		flag_var;

	i = -1;
	init_quotes(&quotes);
	flag_acc = 0;
	flag_var = 0;
	while (line[++i])
	{
		quote_increment(line, i, &quotes);
		if (line[i] == '$' && qts_acc_closed(&quotes))
			flag_var = 1;
		if (1 == flag_var && line[i] == '{')
			flag_acc = 1;
		if (flag_acc == 1 && line[i] == '}')
		{
			flag_var = 0;
			flag_acc = 0;
		}
	}
	return (flag_acc == 0);
}

// <> funccionna
int	check_tok_acc(char *token)
{
	int		i;
	t_quote	quotes;
	int		flag_acc;
	int		flag_var;

	init_quotes(&quotes);
	i = -1;
	flag_acc = 0;
	flag_var = 0;
	while (token[++i])
	{
		quote_increment(token, i, &quotes);
		if (token[i] == '$' && qts_acc_closed(&quotes))
			flag_var = 1;
		if (1 == flag_var && token[i] == '{')
			flag_acc = 1;
		if (flag_acc == 1 && token[i] == '}')
		{
			flag_var = 0;
			flag_acc = 0;
		}
	}
	return (!(flag_acc == 0));
}

int	accolade_not_closed(t_dlist **cmd_list)
{
	t_dlist	*i_node;
	int		i;
	int		flag;

	i_node = *cmd_list;
	flag = 0;
	while (i_node)
	{
		i = 0;
		while (((t_chunk *)i_node->content)->tokens[i] && flag > 1)
		{
			flag = \
				check_tok_acc(((t_chunk *)i_node->content)->tokens[i++]);
			if (flag > 0)
				return (EXIT_FAILURE);
		}
		i_node = i_node->next;
	}
	return (EXIT_SUCCESS);
}

bool	has_bad_var_substitution(char **tks)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (tks && tks[i])
	{
		j = 0;
		while (tks[i][j])
		{
			if (tks[i][j] == '$' && tks[i][j + 1] && tks[i][j + 1] == '{' \
				&& tks[i][j + 2] && tks[i][j + 2] == '}')
				return (true);
			j++;
		}
		i++;
	}
	return (false);
}

bool	bad_var_substitution(t_data *data, t_dlist *cmd_list)
{
	while (cmd_list)
	{
		if (has_bad_var_substitution(((t_chunk *)cmd_list->content)->tokens))
		{
			write (STDERR_FILENO, "-bash: ${}: bad substitution\n", 30);
			data->exit_status = 1;
			return (true);
		}
		cmd_list = cmd_list->next;
	}
	return (false);
}
