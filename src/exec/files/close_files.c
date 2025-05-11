/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 19:30:46 by ofilloux          #+#    #+#             */
/*   Updated: 2025/05/11 20:04:31 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

void	close_files(t_chunk *chunk)
{
	int	i;

	i = 0;
	while (i < chunk->redir_file_count)
	{
		if (chunk->file_open[i])
		{
			close(chunk->file_fd[i]);
			chunk->file_open[i] = false;
		}
		i++;
	}
	return ;
}

void	close_files_if_opened(int *fd_arr, bool *file_open)
{
	int	i;

	i = 0;
	while (fd_arr && fd_arr[i] && *file_open)
	{
		if (file_open[i])
		{
			if (close (fd_arr[i]) == -1)
				perror("Error at closing files: ");
			file_open[i] = false;
		}
		i++;
	}
}
