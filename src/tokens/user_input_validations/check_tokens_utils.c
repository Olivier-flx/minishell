/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_tokens_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 10:46:57 by ofilloux          #+#    #+#             */
/*   Updated: 2025/06/09 10:48:37 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


bool	chunk_is_empty(t_chunk *chk)
{
	return (!(chk->tokens[0]));
}

bool	unique_empty_node(t_data *data, t_dlist *cmd_list)
{
	t_chunk	*chk;

	chk = ((t_chunk *) cmd_list->content);
	if (!cmd_list->next && chunk_is_empty(chk))
	{
		data->exit_status = 0;
		return (true);
	}
	return (false);
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
