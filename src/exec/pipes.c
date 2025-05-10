/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 17:37:47 by ofilloux          #+#    #+#             */
/*   Updated: 2025/05/10 17:40:44 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void close_unecessary_pipes(t_exe *exe, int i)
{
	int j;

	j = 0;
	while (j < exe->total_cmd_count - 1)
	{
		if (j != i && close(exe->pipe_arr[j][0]) == -1){
			printf("(*pipe_arr)[j][0] --> j == %d\n", j); // @confirm : dois-je gerer ainsi ?
			//perror("Error closing pipe_arr[j][0]");
			}
		if (j != i + 1 && close(exe->pipe_arr[j][1])){
			printf("(*pipe_arr)[j][1] --> j == %d\n", j);// @confirm : dois-je gerer ainsi ?
			//perror("Error closing pipe_arr[j][1]");
			}
		j++;
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
}

void	init_pipes_2arr(t_data *data, t_exe *exe)
{
	int i;

	if (!data)
		return;
	if (exe->total_cmd_count < 2)
		return ;
	exe->pipe_arr = malloc(sizeof(int *) * (exe->total_cmd_count - 1));
	if (!exe->pipe_arr)
		strerror(errno);
		//clean_cmds_exit(data, EXIT_FAILURE/* , "Malloc err pipes" */);
	exe->pipe_arr_malloced = true;
	i = 0;
	while (i < exe->total_cmd_count - 1)
	{
		exe->pipe_arr[i] = malloc(sizeof(int) * 2);
		if (!exe->pipe_arr[i])
			strerror(errno);
			// clean_cmds_exit(data, EXIT_FAILURE/* , "Malloc err pipe_arr[i]" */); //@optimize, same as before and // pourrait rendre plus robuste si erreur de malloc
		exe->pipes_malloced[i] = true;
		if (pipe(exe->pipe_arr[i]) == -1)
			strerror(errno);
			// clean_cmds_exit(data, EXIT_FAILURE/* , "Error in pipe : run_pipex" */); //@optimize, same as before
		i++;
	}
}
