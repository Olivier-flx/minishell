/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtins.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 16:04:38 by ofilloux          #+#    #+#             */
/*   Updated: 2025/05/11 16:54:07 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	pick_and_run_builtin(t_data *data, char **argv)
{
	// if (ft_strcmp(argv[0], "cd") == 0)
	// 	return (builtin_cd(data, argv));
	/* else */ if (ft_strcmp(argv[0], "export") == 0)
		return (ft_export(&data->env_list, argv));
	// else if (ft_strcmp(argv[0], "unset") == 0)
	// 	return (ft_unset(data, argv));
	else if (ft_strcmp(argv[0], "exit") == 0)
		return (ft_exit(argv));
	// else if (ft_strcmp(argv[0], "exit") == 0)
		// return (ft_exit(data, argv));
	else if (ft_strcmp(argv[0], "pwd") == 0)
		return (ft_pwd());
	else if (ft_strcmp(argv[0], "env") == 0)
		return (ft_env(data->env_list));
	else if (ft_strcmp(argv[0], "echo") == 0)
		return (ft_echo(data->env_list, argv));
	return (EXIT_FAILURE);
}

void	execute_builtin_in_parent(t_data *data, t_exe *exe, t_chunk *chunk, int i)
{
	close_unecessary_pipes(exe, i - 1);
	redirect_input_file(data, chunk);
	redirect_to_output_file(data, chunk);
	pick_and_run_builtin(data, chunk->argv);
}

void	execute_builtin_in_child(t_data *data, t_exe *exe, t_chunk *chunk, int i)
{
	if ( !data || !exe || !chunk || i < 0)
		return ;
	pick_and_run_builtin(data, chunk->argv);
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
		{
			execute_builtin_in_child (data, exe, chunk, i);
			return (0);
		}
	}
	return (-1);
}
