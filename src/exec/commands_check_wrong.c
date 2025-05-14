/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_check_wrong.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 17:11:08 by ofilloux          #+#    #+#             */
/*   Updated: 2025/05/14 17:17:54 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

static void	append_error_message(t_data *data, char *msg)
{
	char *tmp_msg;

	if (data->exec_info.cmd_err_msg == NULL)
	{
		data->exec_info.cmd_err_msg = msg;
		data->exec_info.has_msg = true;
	}
	else
	{
		tmp_msg = ft_strjoin(data->exec_info.cmd_err_msg, msg);
		ft_free((void **) &data->exec_info.cmd_err_msg);
		ft_free((void **) &msg);
		data->exec_info.cmd_err_msg = tmp_msg;
	}
}

static void	handle_invalid_command(t_data *data, t_chunk *chunk, int i)
{
	char	*msg;
	int		flag;

	data->exec_info.command_err_count++;
	data->exec_info.cmd_is_valid_arr[i] = false;
	if (i == data->exec_info.total_cmd_count)
		data->exec_info.last_status_code = 127;
	else
		data->exec_info.last_status_code = 0;
	flag = usr_input_got_slash(chunk->argv[0]);
	msg = get_msg(data, flag, chunk->argv[0]);
	append_error_message(data, msg);
}

static void	handle_chunk_command(t_data *data, t_chunk *chunk, int i)
{
	if (access(chunk->argv[0], X_OK) != 0 && !is_builtin(chunk->argv[0]))
		handle_invalid_command(data, chunk, i);
	else
		command_is_valid(data, i);
}

void	check_wrong_commands(t_data *data)
{
	int		i;
	t_dlist	*i_node;

	i = 0;
	i_node = data->cmd_list;
	while (i < data->nb_chunks && i_node)
	{
		t_chunk *chunk = (t_chunk *)i_node->content;
		if (!chunk->argv || chunk->type != CMD)
		{
			i_node = i_node->next;
			continue ;
		}
		handle_chunk_command(data, chunk, i);
		i++;
		i_node = i_node->next;
	}
}

/* void	check_wrong_commands(t_data *data)
{
	int		i;
	int		flag;
	char	*tmp_msg;
	char	*msg;
	t_chunk	*chunk;
	t_dlist	*i_node;

	flag = 0;
	tmp_msg = NULL;
	msg = NULL;
	i = 0;
	chunk = NULL;
	i_node = data->cmd_list;
	while (i < data->nb_chunks && i_node) // à modifier en cas de heredoc
	{
		chunk = (t_chunk *)i_node->content;
		if (!chunk->argv || chunk->type != CMD)
		{
			i_node = i_node->next;
			continue ;
		}
		if (access(chunk->argv[0], X_OK) != 0 && !is_builtin(chunk->argv[0]))
		{
			data->exec_info.command_err_count ++;

			data->exec_info.cmd_is_valid_arr[i] = false;
			data->exec_info.last_status_code = 0;
			if (i == data->exec_info.total_cmd_count)
				data->exec_info.last_status_code = 127;
			flag = usr_input_got_slash(chunk->argv[0]);
			msg = get_msg(data, flag, chunk->argv[0]);
			if (data->exec_info.cmd_err_msg == NULL)
			{
				data->exec_info.cmd_err_msg = msg;
				data->exec_info.has_msg = true;
			}
			else
			{
				tmp_msg = ft_strjoin(data->exec_info.cmd_err_msg, msg);
				ft_free((void **) &data->exec_info.cmd_err_msg);
				ft_free((void **) &msg);
				data->exec_info.cmd_err_msg = tmp_msg;
			}
		}
		else
			command_is_valid(data, i);
		i++;
		i_node = i_node->next;
	}
} */
