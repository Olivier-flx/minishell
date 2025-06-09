/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_close.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 10:41:01 by ofilloux          #+#    #+#             */
/*   Updated: 2025/06/09 22:04:27 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	close_unecessary_pipes(t_exe *exe, int i)
{
	int	j;

	j = 0;

	while (j < exe->total_cmd_count - 1)
	{
		if (j != i && close(exe->pipe_arr[j][0]) == -1)
			perror("Error : close pipe_arr[j][0] :");
		if (j != i + 1 && close(exe->pipe_arr[j][1]))
			perror("Error : close pipe_arr[j][1] :");
		j++;
	}
}

// void	close_unecessary_pipes(t_exe *exe, int i)
// {
// 	int	j;

// 	j = 0;
// 	while (j < exe->total_cmd_count - 1)
// 	{
// 		if (j != i && close(exe->pipe_arr[j][0]) == -1)
// 			perror("Error : close pipe_arr[j][0] :");
// 		if (j != i + 1 && close(exe->pipe_arr[j][1]))
// 			perror("Error : close pipe_arr[j][1] :");
// 		j++;
// 	}
// }

void	close_all_pipes_child(t_exe *exe)
{
	int	i = 0;

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
		fprintf(stderr, "[pid %d] closing all pipes [%d][%d]\n", getpid(), j, exe->pipe_arr[j][0]);
		if (close((*pipe_arr)[j][0]) == -1)
			perror("Err close_all_pipes [j][0]");
		if (close((*pipe_arr)[j][1]) == -1)
			perror("Err close_all_pipes [j][1]");
		j++;
	}
	free_pipes_arr(*pipe_arr, exe);
	*pipe_arr = NULL;
}
