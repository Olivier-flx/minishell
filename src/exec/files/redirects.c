/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 17:06:53 by ofilloux          #+#    #+#             */
/*   Updated: 2025/07/14 10:37:16 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

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
		ft_putstr_fd("Error open(), last file\n", STDERR_FILENO);
		return ;
	}
	chunk->file_open[lst_file] = true;
	if (dup2(chunk->file_fd[lst_file], STDOUT_FILENO) == -1)
		perror("dup2");
	close(chunk->file_fd[lst_file]);
	chunk->file_open[lst_file] = false;
	chunk->file_fd[lst_file] = -1;
}
