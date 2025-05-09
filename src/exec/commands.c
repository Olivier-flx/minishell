/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 18:10:10 by ofilloux          #+#    #+#             */
/*   Updated: 2025/05/09 19:46:06 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

char	*get_msg(int flag, char *arg)
{
	char	*msg;
	char	*tmp;

	msg = NULL;
	tmp = NULL;
	if (flag == 1)
		msg = ft_strjoin("zsh: no such file or directory: ", arg);
	else
		msg = ft_strjoin("zsh: command not found: ", arg);
	if (msg && msg[0])
	{
		tmp = msg;
		msg = ft_strjoin(tmp, "\n");
		free (tmp);
	}
	return (msg);
}

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

void	command_is_valid(t_data *data, int i)
{
	data->exec_info.cmd_is_valid_arr[i] = true;
	data->exec_info.valid_cmd_count++;
}

void	check_wrong_commands(t_data *data)
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
	//debug_print_cmd_list(&data->cmd_list); //@debug
	while (i < data->nb_chunks && i_node) // à modifier en cas de heredoc
	{
		chunk = (t_chunk *)i_node->content;
		//printf ("chunk[%i]->argv[0] = `%s` ; type = `%d`\n", chunk->index ,chunk->argv[0], chunk->type);// @debug
		if (!chunk->argv || chunk->type != CMD)
		{
			i_node = i_node->next;
			continue ;
		}
		if (access(chunk->argv[0], X_OK) != 0)
		{
			data->exec_info.command_err_count ++;

			data->exec_info.cmd_is_valid_arr[i] = false;
			data->exec_info.last_status_code = 0;
			if (i == data->exec_info.total_cmd_count)
				data->exec_info.last_status_code = 127;
			flag = usr_input_got_slash(chunk->argv[0]);
			msg = get_msg(flag, chunk->argv[0]);
			if (data->exec_info.cmd_err_msg == NULL)
			{
				data->exec_info.cmd_err_msg = msg;
				data->exec_info.has_msg = true;
			}
			else
			{
				tmp_msg = ft_strjoin(data->exec_info.cmd_err_msg, msg);
				free(data->exec_info.cmd_err_msg);
				free(msg);
				data->exec_info.cmd_err_msg = tmp_msg;
			}
		}
		else
			command_is_valid(data, i);
		i++;
		i_node = i_node->next;
	}
	if (data->exec_info.cmd_err_msg != NULL && data->exec_info.command_err_count == data->exec_info.total_cmd_count)
		printf("%s\n", data->exec_info.cmd_err_msg);
		//clean_cmds_exit(data, data->exec_info.last_status_code);
}

void	init_cmd_vect(t_data *data, t_dlist **cmd_list, t_exe *exec_info)
{
	t_dlist	*i_node;
	t_chunk	*chunk;
	int		i;

	i_node = *cmd_list;
	chunk = NULL;
	i = 0;
	while (i_node)
	{
		chunk = (t_chunk *) i_node->content;
		if (chunk->type == CMD)
		{
			exec_info->cmd_is_valid_arr[i] = false;
			if (usr_input_got_slash(chunk->argv[0]) == 0)
			{
				if (exec_info->env_path_found == false)
					get_path(chunk->argv[0], exec_info, data->env_list);
				if (exec_info->env_path_found == true)
				{
					chunk->argv_0_nopath = ft_strdup(chunk->argv[0]); // @ test id 1
					free (chunk->argv[0]);
					chunk->argv[0] = ft_strjoin(exec_info->env_path, chunk->argv_0_nopath);
				}
			}
		i++;
		}
		i_node = i_node->next;
	}
}
/* dans piper 	char	***cmd_vect;
cmd_vect = cmd_list et cmd_vect[0] = cmd_list->content->argv */

static void	init_bool_pipes_malloced(t_data * data, t_exe *exe_info)
{
	int	i;

	i = 0;
	if (exe_info->total_cmd_count < 2)
		return ;
	exe_info->pipes_malloced = malloc(sizeof(bool) * (exe_info->total_cmd_count - 1));
	if (!exe_info->pipes_malloced)
		clean_cmds_exit(data, EXIT_FAILURE);
	while (i < exe_info->total_cmd_count - 1)
	{
		exe_info->pipes_malloced[i] = false;
		i++;
	}
}

int	count_cmd(t_dlist **cmd_list)
{
	t_dlist *i_node;
	int	k;

	i_node = *cmd_list;
	k = 0;
	while (i_node)
	{

		if (((t_chunk *) i_node->content)->type == CMD)
			k++;
		i_node = i_node->next;
	}
	return (k);
}

void	init_cmd_is_valid_arr(t_exe *exe_info, int nb_cmd)
{
	exe_info->cmd_is_valid_arr = NULL;
	exe_info->cmd_is_valid_arr_malloced = false;
	exe_info->cmd_is_valid_arr = malloc(sizeof(bool) * (nb_cmd + 1));
	if (!exe_info->cmd_is_valid_arr)
		return ;
	exe_info->cmd_is_valid_arr_malloced = true;
	return ;
}

void	init_cmd(t_data *data)
{
	data->exec_info.total_cmd_count = count_cmd(&data->cmd_list);
	init_cmd_is_valid_arr(&data->exec_info, data->exec_info.total_cmd_count);
	data->exec_info.env_path = NULL;
	data->exec_info.env_path_found = false;
	data->exec_info.pid_arr = NULL;
	data->exec_info.pid_arr_malloced = false;
	data->exec_info.pipe_arr = false;
	data->exec_info.pipe_arr_malloced = false;
	data->exec_info.pipes_malloced = false;
	data->exec_info.cmd_err_msg = NULL;
	data->exec_info.has_msg = false;
	data->exec_info.valid_cmd_count = 0;
	data->exec_info.command_err_count = 0;
	data->exec_info.last_status_code = 0;
	init_cmd_vect(data, &data->cmd_list, &data->exec_info);
	check_wrong_commands(data);
	init_bool_pipes_malloced(data, &data->exec_info);
	return ;
}
