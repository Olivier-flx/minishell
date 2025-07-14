/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 17:55:52 by ofilloux          #+#    #+#             */
/*   Updated: 2025/07/14 16:09:39 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

static void	handle_pipex_exec(t_data *data, t_exe *exe, t_chunk *chunk, int i)
{
	int	status_code_cpy;

	status_code_cpy = 0;
	if (0 != execve_builtin_in_child(data, exe, chunk, i) && chunk->argv && \
			0 == chunk->chunk_exec_return_status_code)
		execve(chunk->exec, chunk->argv, ft_env_to_array(data->env_list));
	else
	{
		status_code_cpy = chunk->chunk_exec_return_status_code;
		free_resources(data, true, true);
		exit(status_code_cpy);

	}
	if (exe->total_cmd_count > 1)
	{
		status_code_cpy = data->exit_status;
		free_resources(data, true, true);
		exit (status_code_cpy);
	}
}

int	run_pipex(t_data *data, t_exe *exe, t_chunk *chunk, int i)
{
	close_unecessary_pipes(exe, i);
	redirect_input_file(data, chunk);
	redirect_to_output_file(data, chunk);
	if (i > 0 && !chunk->has_input_redir && dup2(exe->pipe_arr[i - 1][0], \
		STDIN_FILENO) == -1)
		perror("dup2 input");
	if (i >= 0 && i < exe->total_cmd_count - 1)
		close(exe->pipe_arr[i][0]);
	if (i < exe->total_cmd_count - 1 && !chunk->has_redir \
			&& dup2(exe->pipe_arr[i][1], STDOUT_FILENO) == -1)
		perror("dup2 redir");
	if (i < exe->total_cmd_count - 1)
		close(exe->pipe_arr[i][1]);
	handle_pipex_exec(data, exe, chunk, i);
	return (EXIT_SUCCESS);
}

void	process_invalide_cmd(t_data *data, t_exe *exe, int i)
{
	char	buf[10];
	int		j;

	(void) data;
	if (i > 0 && i < exe->total_cmd_count)
	{
		data->exe_nfo.pid_arr[i] = fork();
		if (data->exe_nfo.pid_arr[i] == 0)
		{
			j = 0;
			while (j < exe->total_cmd_count - 1)
			{
				if (j != i - 1)
					close(exe->pipe_arr[j][0]);
				close(exe->pipe_arr[j][1]);
				j++;
			}
			while (read(exe->pipe_arr[i - 1][0], buf, sizeof(buf)) > 0)
				continue ;
			close(exe->pipe_arr[i - 1][0]);
			data->exit_status = 127;
			execve("/bin/true", (char *[]){"true", NULL}, NULL);
			exit(127);
		}
	}
}

void	process_command_iteration(t_data *data, t_chunk *chunk, int i, \
									int *valid_cmd_i)
{
	chunk->chunk_exec_return_status_code = 0;
	listen_heredocs(data, chunk);
	if (!chunk->argv || data->exe_nfo.cmd_is_valid_arr[*valid_cmd_i] == true)
	{
		if (run_builtins(data, &data->exe_nfo, chunk, i) != 1)
		{
			data->exe_nfo.pid_arr[i] = fork();
			if (data->exe_nfo.pid_arr[i] == -1)
				perror("Fork");
			if (data->exe_nfo.last_status_code == 0)
				data->exit_status = 0;
			if (data->exe_nfo.pid_arr[i] == 0)
			{
				reset_signals_to_default();
				run_pipex(data, &data->exe_nfo, chunk, i);
			}
		}
		if (chunk->argv)
			(*valid_cmd_i)++;
	}
	else
		process_invalide_cmd(data, &data->exe_nfo, i);
	close_heredocs_pipes(chunk);
}

/* void	exec_cmds(t_data *data, int i)
{
	int		valid_cmd_i;
	t_dlist	*i_node;

	i_node = data->cmd_list;
	valid_cmd_i = 0;
	while (i <  data->exe_nfo.total_cmd_count)
	{
		if (i_node && (t_chunk *)i_node->content
			&& ((t_chunk *)i_node->content)->type != CMD)
		{
			i_node = i_node->next;
			continue ;
		}
		listen_heredocs(data, (t_chunk *)i_node->content);
		if (data->exe_nfo.cmd_is_valid_arr[i] == true)
		{
			if (1 != run_builtins(data, &data->exe_nfo,
				((t_chunk *)i_node->content), i))
			{
				data->exe_nfo.pid_arr[valid_cmd_i] = fork();
				if (data->exe_nfo.pid_arr[valid_cmd_i] == -1)
					strerror(errno);
				if (data->exe_nfo.pid_arr[valid_cmd_i] == 0)
					run_pipex (data, &data->exe_nfo,
						((t_chunk *)i_node->content), i);
			}
			valid_cmd_i++;
		}
		close_heredocs_pipes((t_chunk *)i_node->content);
		i++;
		i_node = i_node->next;
	}
} */
