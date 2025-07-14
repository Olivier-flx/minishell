/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtins.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 16:04:38 by ofilloux          #+#    #+#             */
/*   Updated: 2025/07/14 14:35:16 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	pick_and_run_builtin(t_data *data, char **argv, bool child)
{
	int	built_num;

	built_num = get_builtin_int(argv[0]);
	if (built_num == 0)
		return (ft_echo(data->env_list, argv));
	else if (built_num == 1)
		return (ft_cd(&data->env_list, argv));
	else if (built_num == 2)
		return (ft_pwd());
	else if (built_num == 3)
		return (ft_export(&data->env_list, argv));
	else if (built_num == 4)
		return (ft_unset(&data->env_list, argv));
	else if (built_num == 5)
		return (ft_env(data->env_list));
	else if (built_num == 6 && !child)
		return (ft_exit(data, argv));
	else if (built_num == 6 && child)
		return (ft_exit_child(data, argv));
	return (EXIT_FAILURE);
}

static void	builtin_exit_handler(t_data *data, t_exe *exe, int cpy_status_code)
{
	if (data->exit_required)
	{
		free_resources(data, true, true);
		exit(cpy_status_code);
	}
	close_all_pipes_child(exe);
	free_resources(data, true, true);
	exit (cpy_status_code);
}

int	execve_builtin_in_child(t_data *data, t_exe *exe, t_chunk *chunk, int i)
{
	int	cpy_status_code;

	cpy_status_code = 0;
	if (chunk && chunk->argv && is_builtin(chunk->argv[0]))
	{
		if (exe->total_cmd_count > 1)
		{
			if (!data || !exe || !chunk || i < 0)
				return (EXIT_FAILURE);
			if (get_builtin_int(chunk->argv[0]) == 6)
				close_all_pipes_child(exe);
			if (0 == chunk->chunk_exec_return_status_code)
				cpy_status_code = pick_and_run_builtin(data, chunk->argv, 1);
			else
				cpy_status_code = chunk->chunk_exec_return_status_code;
			builtin_exit_handler(data, exe, cpy_status_code);
			return (EXIT_SUCCESS);
		}
	}
	else
		close_all_pipes_child(exe);
	return (EXIT_FAILURE);
}

void	execute_builtin_in_parent(t_data *data, t_exe *exe, \
		t_chunk *chunk, int i)
{
	int	saved_stdin;
	int	saved_stdout;

	(void)exe;
	(void) i;
	save_stdin_stdout(&saved_stdin, &saved_stdout);
	redirect_input_file(data, chunk);
	redirect_to_output_file(data, chunk);
	if (0 == chunk->chunk_exec_return_status_code)
		data->exit_status = pick_and_run_builtin(data, chunk->argv, false);
	else
		data->exit_status = chunk->chunk_exec_return_status_code;
	restor_stdin_stdout(&saved_stdin, &saved_stdout);
	if (data->exit_required)
	{
		write(STDERR_FILENO, "exit\n", 5);
		exit(data->exit_code);
	}
}

int	run_builtins(t_data *data, t_exe *exe, t_chunk *chunk, int i)
{
	if (chunk && chunk->argv && is_builtin(chunk->argv[0]))
	{
		if (exe->total_cmd_count == 1)
		{
			execute_builtin_in_parent(data, exe, chunk, i);
			return (1);
		}
		else
			return (0);
	}
	return (-1);
}
