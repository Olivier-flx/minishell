/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_close.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 10:41:01 by ofilloux          #+#    #+#             */
/*   Updated: 2025/06/14 17:21:15 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

/**
 * @brief Closes all pipe fd that are not needed by the current process.
 *
 * This function iterates through all pipes and closes:
 *   - the read end (`pipe_arr[j][0]`) if the index `j` is not equal to `i`
 *     (ie. let open the read end only for the i command)
 *   - the write end (`pipe_arr[j][1]`) if the index `j` is not equal to `i + 1`
 *     (ie. let open the write end only for the i command)
 *
 * @param exe Pointer to a `t_exe` structure containing:
 *            - `pipe_arr`: an array of pipes (each a pair of file descriptors),
 *            - `total_cmd_count`: the total number of commands in the pipeline.
 * @param i   Index of the current command in the pipeline.
 */
void	close_unecessary_pipes(t_exe *exe, int i)
{
	int	pipe_i;

	pipe_i = 0;
	while (pipe_i < exe->total_cmd_count - 1)
	{
		if (pipe_i != i && close(exe->pipe_arr[pipe_i][0]) == -1)
			perror("Error : close pipe_arr[pipe_i][0] :");
		if (pipe_i != i + 1 && close(exe->pipe_arr[pipe_i][1]) == -1)
			perror("Error : close pipe_arr[pipe_i][1] :");
		pipe_i++;
	}
}

/**
 * @brief Closes all pipe file descriptors in a child process.
 *
 * This function iterates over the `pipe_arr` array in the `t_exe` structure
 * and closes both ends (read and write) of each pipe if they are still open
 * (i.e., not equal to -1). It is intended to be used in child processes
 * when executing a series of piped commands.
 *
 * @param exe Pointer to a `t_exe` structure containing:
 *            - `pipe_arr`: an array of pipes
 * 							(each pipe is a pair of file descriptors),
 *            - `total_cmd_count`: the total number of commands in the pipeline.
 *
 * @note This function does not free the memory allocated for `pipe_arr`; it only
 *       closes the file descriptors.
 * 		It should only be called in child processes.
 */
void	close_all_pipes_child(t_exe *exe)
{
	int	i;

	i = 0;
	while (i < exe->total_cmd_count - 1)
	{
		if (exe->pipe_arr[i][0] != -1)
			close(exe->pipe_arr[i][0]);
		if (exe->pipe_arr[i][1] != -1)
			close(exe->pipe_arr[i][1]);
		i++;
	}
}

void	close_all_pipes(t_exe *exe, int ***pipe_arr)
{
	int	j;

	j = 0;
	while (j < exe->total_cmd_count - 1)
	{
		if (close((*pipe_arr)[j][0]) == -1)
			perror("Err close_all_pipes [j][0]");
		if (close((*pipe_arr)[j][1]) == -1)
			perror("Err close_all_pipes [j][1]");
		j++;
	}
	free_pipes_arr(*pipe_arr, exe);
	*pipe_arr = NULL;
}
