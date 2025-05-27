/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_input_validation.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 15:14:36 by ofilloux          #+#    #+#             */
/*   Updated: 2025/05/27 21:27:03 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

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
		// if (flag_acc == 1 && line[i] != '{' && line[i] != '}')
		// 	k++;
		if (flag_acc == 1 && line[i] == '}')
		{
			flag_var = 0;
			flag_acc = 0;
		}
	}
	return (flag_acc == 0);
}

// <> funccionna
int	check_tocken_accolade(char *token)
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
		if(token[i] == '$' && qts_acc_closed(&quotes))
			flag_var = 1;
		if (1 == flag_var && token[i] == '{')
			flag_acc = 1;
		// if (flag_acc == 1 && token[i] != '{' && token[i] != '}')
		// 	k++;
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
	int flag;

	i_node = *cmd_list;
	flag = 0;
	while(i_node)
	{
		i = 0;
		while (((t_chunk *)i_node->content)->tokens[i] && flag > 1)
		{
			flag = check_tocken_accolade(((t_chunk *)i_node->content)->tokens[i++]);
			if(flag > 0)
				return (EXIT_FAILURE);
		}
		i_node = i_node->next;
	}
	return (EXIT_SUCCESS);
}

