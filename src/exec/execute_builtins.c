/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtins.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 16:04:38 by ofilloux          #+#    #+#             */
/*   Updated: 2025/05/19 18:05:11 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	pick_and_run_builtin(t_data *data, char **argv)
{
	if (ft_strcmp(argv[0], "cd") == 0)
		return (ft_cd(&data->env_list, argv));
	else if (ft_strcmp(argv[0], "export") == 0)
		return (ft_export(&data->env_list, argv));
	else if (ft_strcmp(argv[0], "unset") == 0)
		return (ft_unset(&data->env_list, argv));
	else if (ft_strcmp(argv[0], "exit") == 0)
		return (ft_exit(data, argv));
	else if (ft_strcmp(argv[0], "pwd") == 0)
		return (ft_pwd());
	else if (ft_strcmp(argv[0], "env") == 0)
		return (ft_env(data->env_list));
	//debug_print_cmd_list(&data->cmd_list);
	if (ft_strcmp(argv[0], "echo") == 0)
		return (ft_echo(data->env_list, argv));
	return (EXIT_FAILURE);
}

void	execute_builtin_in_parent(t_data *data, t_exe *exe, t_chunk *chunk, int i)
{
	int	saved_stdin;
	int	saved_stdout;

	saved_stdin  = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	close_unecessary_pipes(exe, i - 1);
	redirect_input_file(data, chunk);
	redirect_to_output_file(data, chunk);
	data->exit_status = pick_and_run_builtin(data, chunk->argv);
	dup2(saved_stdin,  STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
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


int	execve_builtin_in_child(t_data *data, t_exe *exe, t_chunk *chunk, int i)
{
	if (chunk && chunk->argv && is_builtin(chunk->argv[0]))
	{
		if (exe->total_cmd_count > 1)
		{
			if ( !data || !exe || !chunk || i < 0)
				return (EXIT_FAILURE);
			data->exit_status = pick_and_run_builtin(data, chunk->argv);
			return (EXIT_SUCCESS);
		}
	}
	return (EXIT_FAILURE);
}
