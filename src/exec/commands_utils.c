/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 17:19:38 by ofilloux          #+#    #+#             */
/*   Updated: 2025/07/12 10:50:45 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

char	*get_error_access_msg(t_data *data, char *arg)
{
	char	*msg;
	char	*tmp;

	msg = NULL;
	tmp = NULL;
	tmp = ft_strjoin3("minishell: ", arg, ": ");
	msg = ft_strjoin3(tmp, strerror(errno), "\n");
	ft_free ((void **)&tmp);
	data->exit_status = 126;
	return (msg);
}

char	*get_msg(t_data *data, int flag, char *arg)
{
	char	*msg;
	char	*tmp;

	msg = NULL;
	tmp = NULL;
	if (flag == 1 && (ft_isalnum(arg[0]) || arg[0] == '.' || arg[0] == '/'))
		msg = ft_strjoin("bash: no such file or directory: ", arg);
	else if (flag == 2)
		msg = ft_strjoin3("bash: ", arg, ": Is a directory");
	else
	{
		msg = ft_strjoin(arg, ": command not found");
		data->exit_status = 127;
	}
	if (msg && msg[0])
	{
		tmp = msg;
		msg = ft_strjoin(tmp, "\n");
		ft_free ((void **)&tmp);
	}
	return (msg);
}

/**
 * @return 1 if a slash is present;
 * @return 0 if no slash is in the string
 */
int	usr_input_got_slash(char *str)
{
	int	i;
	int	flag;

	if (!str)
		return (-1);
	i = 0;
	flag = 0;
	while (str[i])
	{
		if (str[i] == '/')
		{
			flag = 1;
			break ;
		}
		i++;
	}
	return (flag);
}

void	command_is_valid(t_data *data, t_chunk *chunk, int i)
{
	if (get_builtin_int(chunk->argv[0]) == 1 \
		&& usr_input_got_slash(chunk->argv[0]))
	{
		handle_invalid_command(data, chunk, i);
		data->exit_status = 127;
		return ;
	}
	data->exe_nfo.cmd_is_valid_arr[i] = true;
	data->exe_nfo.valid_cmd_count++;
}

int	count_cmd(t_dlist **cmd_list)
{
	t_dlist	*i_node;
	int		k;

	i_node = *cmd_list;
	k = 0;
	while (i_node)
	{
		if (((t_chunk *) i_node->content)->type == CMD \
			|| ((t_chunk *) i_node->content)->type == EMPTY)
			k++;
		i_node = i_node->next;
	}
	return (k);
}
