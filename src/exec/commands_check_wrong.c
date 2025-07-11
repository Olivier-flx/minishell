/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_check_wrong.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 17:11:08 by ofilloux          #+#    #+#             */
/*   Updated: 2025/07/11 19:16:55 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

static void	append_error_message(t_data *data, char *msg)
{
	char	*tmp_msg;

	if (data->exe_nfo.cmd_err_msg == NULL)
	{
		data->exe_nfo.cmd_err_msg = msg;
		data->exe_nfo.has_msg = true;
	}
	else
	{
		tmp_msg = ft_strjoin(data->exe_nfo.cmd_err_msg, msg);
		ft_free((void **) &data->exe_nfo.cmd_err_msg);
		ft_free((void **) &msg);
		data->exe_nfo.cmd_err_msg = tmp_msg;
	}
}

/**
 * @brief Handles the case where the command is a directory.
 *
 * Marks the command as invalid and appends an appropriate error message.
 * If it's the last command in the pipeline, sets the exit status to 126
 * (indicating a permission problem or non-executable).
 *
 * @param data	Structure containing the shell's global data.
 * @param chunk	Chunk representing the command.
 * @param i		Index of the command in the execution array.
 */
void	handle_invalid_command(t_data *data, t_chunk *chunk, int i)
{
	char	*msg;
	int		flag;

	data->exe_nfo.command_err_count++;
	data->exe_nfo.cmd_is_valid_arr[i] = false;
	if (i == data->exe_nfo.total_cmd_count - 1)
		data->exe_nfo.last_status_code = 127;
	else
		data->exe_nfo.last_status_code = 0;
	if (access(chunk->argv[0], X_OK) == -1 && errno != 2)
		msg = get_error_access_msg(data, chunk->argv[0]);
	else
	{
		flag = usr_input_got_slash(chunk->argv[0]);
		msg = get_msg(data, flag, chunk->argv[0]);
	}
	append_error_message(data, msg);
}

/**
 * @brief Handles the case where the command is a directory.
 *
 * Marks the command as invalid and appends an appropriate error message.
 * If it's the last command in the pipeline, sets the exit status to 126
 * (indicating a permission problem or non-executable).
 *
 * @param data	Structure containing the shell's global data.
 * @param chunk	Chunk representing the command.
 * @param i		Index of the command in the execution array.
 */
void	cmd_is_dir(t_data *data, t_chunk *chunk, int i)
{
	data->exe_nfo.cmd_is_valid_arr[i] = false;
	append_error_message(data, get_msg(data, 2, chunk->argv[0]));
	if (i == data->exe_nfo.total_cmd_count - 1)
	{
		data->exe_nfo.last_status_code = 126;
		data->exit_status = 126;
	}
	else
		data->exe_nfo.last_status_code = 0;
}

/**
 * @brief Checks and validates a single command chunk.
 *
 * - If the command is a builtin, it is marked as valid.
 * - If the command doesn't exist (stat fails), it's marked invalid.
 * - If the command is a directory, it's marked invalid.
 * - If it's a regular file without execute permission, it's marked invalid.
 * Otherwise, the command is marked valid.
 *
 * @param data	Structure containing the shell's global data.
 * @param chunk	Chunk representing the command.
 * @param i		Index of the command in the execution array.
 *
 * @see	<sys/stat.h> & man 2 stat
 */
static void	handle_chunk_command(t_data *data, t_chunk *chunk, int i)
{
	struct stat	s;
	int			s_ret;

	if (is_builtin(chunk->argv[0]))
	{
		command_is_valid(data, chunk, i);
		return ;
	}
	s_ret = stat(chunk->argv[0], &s);
	if (s_ret != 0)
	{
		handle_invalid_command(data, chunk, i);
		return ;
	}
	if (s_ret == 0 && (s.st_mode & S_IFMT) == S_IFDIR)
		cmd_is_dir(data, chunk, i);
	else if (s_ret == 0 && (s.st_mode & S_IFMT) == S_IFREG \
			&& access(chunk->argv[0], X_OK) != 0 && !is_builtin(chunk->argv[0]))
		handle_invalid_command(data, chunk, i);
	else
		command_is_valid(data, chunk, i);
}

/**
 * @brief Iterates over all command chunks to detect and flag invalid commands.
 *
 * Goes through each command chunk, skipping EMPTY types
 * or those without arguments.
 * For each valid command, it invokes handle_chunk_command to perform
 * validation and path checks.
 *
 * @param data	Structure containing the shell's global data,
 * 				including the command list.
 */
void	check_wrong_commands(t_data *data)
{
	int		i;
	t_dlist	*i_node;
	t_chunk	*chunk;

	i = 0;
	i_node = data->cmd_list;
	while (i < data->nb_chunks && i_node)
	{
		chunk = (t_chunk *)i_node->content;
		if (!chunk->argv || chunk->type != CMD)
		{
			if (chunk->type == EMPTY)
				i++;
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
			data->exe_nfo.command_err_count ++;

			data->exe_nfo.cmd_is_valid_arr[i] = false;
			data->exe_nfo.last_status_code = 0;
			if (i == data->exe_nfo.total_cmd_count)
				data->exe_nfo.last_status_code = 127;
			flag = usr_input_got_slash(chunk->argv[0]);
			msg = get_msg(data, flag, chunk->argv[0]);
			if (data->exe_nfo.cmd_err_msg == NULL)
			{
				data->exe_nfo.cmd_err_msg = msg;
				data->exe_nfo.has_msg = true;
			}
			else
			{
				tmp_msg = ft_strjoin(data->exe_nfo.cmd_err_msg, msg);
				ft_free((void **) &data->exe_nfo.cmd_err_msg);
				ft_free((void **) &msg);
				data->exe_nfo.cmd_err_msg = tmp_msg;
			}
		}
		else
			command_is_valid(data, i);
		i++;
		i_node = i_node->next;
	}
} */
