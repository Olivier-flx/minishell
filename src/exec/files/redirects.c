/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 17:06:53 by ofilloux          #+#    #+#             */
/*   Updated: 2025/07/14 11:52:13 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

static int	check_r_file_rights(t_chunk *chunk)
{
	int	i;

	i = 0;
	while (i < chunk->redir_file_count)
	{
		if (chunk->chunk_exec_return_status_code != 0)
			return (1);
		if (-1 == access(chunk->redir_files[i], R_OK))
		{
			chunk->chunk_exec_return_status_code = 1;
			printf("minishell: %s: %s\n", \
			chunk->redir_files[i], strerror(errno));
			return (1);
		}
		i++;
	}
	return (0);
}

void	redirect_to_output_file(t_data *data, t_chunk *chunk)
{
	int	lst_file;

	if (!data || chunk->redir_file_count == 0)
		return ;
	if (check_r_file_rights(chunk) == 1)
		return ;
	lst_file = chunk->redir_file_count - 1;
	chunk->file_fd[lst_file] = open_redir_file(chunk, lst_file);
	if (chunk->file_fd[lst_file] < 0)
	{
		ft_putstr_fd("Error open() r, last file\n", STDERR_FILENO);
		return ;
	}
	chunk->file_open[lst_file] = true;
	if (dup2(chunk->file_fd[lst_file], STDOUT_FILENO) == -1)
		perror("dup2");
	close(chunk->file_fd[lst_file]);
	chunk->file_open[lst_file] = false;
	chunk->file_fd[lst_file] = -1;
}
