/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtins.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 16:04:38 by ofilloux          #+#    #+#             */
/*   Updated: 2025/07/07 18:09:54 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	pick_and_run_builtin(t_data *data,  char **argv)
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
	else if (built_num == 6)
		return (ft_exit(data, argv));


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
	data->exit_status = pick_and_run_builtin(data, chunk->argv);
	restor_stdin_stdout(&saved_stdin, &saved_stdout);
	if (data->exit_required)
		exit(data->exit_code);
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
