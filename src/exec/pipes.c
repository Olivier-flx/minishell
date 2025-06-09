/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 17:37:47 by ofilloux          #+#    #+#             */
/*   Updated: 2025/06/09 10:44:01 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	init_bool_pipes_malloced(t_data *data, t_exe *exe_info)
{
	int	i;

	if (!data)
		return ;
	i = 0;
	if (exe_info->total_cmd_count < 2)
		return ;
	exe_info->pipes_malloced = \
			malloc(sizeof(bool) * (exe_info->total_cmd_count - 1));
	if (!exe_info->pipes_malloced)
		perror("Pipes Malloc : ");
	while (i < exe_info->total_cmd_count - 1)
	{
		exe_info->pipes_malloced[i] = false;
		i++;
	}
}

void	init_pipes_2arr(t_data *data, t_exe *exe)
{
	int	i;

	if (!data || exe->total_cmd_count < 2)
		return ;
	exe->pipe_arr = malloc(sizeof(int *) * (exe->total_cmd_count - 1));
	if (!exe->pipe_arr)
		ft_putstr_fd("pipe_arr Malloc error \n", STDERR_FILENO);
	exe->pipe_arr_malloced = true;
	i = 0;
	while (i < exe->total_cmd_count - 1)
	{
		exe->pipe_arr[i] = malloc(sizeof(int) * 2);
		if (!exe->pipe_arr[i])
			ft_putstr_fd("*pipe_arr Malloc error \n", STDERR_FILENO);
		exe->pipes_malloced[i] = true;
		if (pipe(exe->pipe_arr[i]) == -1)
			ft_putstr_fd("*pipe_malloced error \n", STDERR_FILENO);
		i++;
	}
}

void	init_pipes_2arr_for_heredoc(t_data *data, t_chunk *chunk)
{
	int	i;

	if (!data)
		return ;

	chunk->heredoc_pipe_arr_malloced = false;
	chunk->heredoc_pipe_arr = malloc(sizeof(int *) * (chunk->nb_heredocs));
	if (!chunk->heredoc_pipe_arr)
		strerror(errno);
	chunk->heredoc_pipe_arr_malloced = true;
	i = 0;
	while (i < chunk->nb_heredocs)
	{
		chunk->heredoc_pipe_arr[i] = malloc(sizeof(int) * 2);
		if (!chunk->heredoc_pipe_arr[i])
			strerror(errno);
		if (pipe(chunk->heredoc_pipe_arr[i]) == -1)
			strerror(errno);
		i++;
	}
}

void	close_heredocs_pipes(t_chunk *chunk)
{
	int	i;

	if (!chunk->has_here_doc)
		return ;
	i = 0;
	while (i < chunk->nb_heredocs)
	{
		if (chunk->heredoc_pipe_arr_malloced && chunk->heredoc_pipe_arr[i])
		{
			close(chunk->heredoc_pipe_arr[i][0]);
			close(chunk->heredoc_pipe_arr[i][1]);
			ft_free((void **) &chunk->heredoc_pipe_arr[i]);
		}
		i++;
	}
	if (chunk->heredoc_pipe_arr_malloced)
		ft_free((void **) &chunk->heredoc_pipe_arr);
}
