/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_check_access.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 10:27:36 by ofilloux          #+#    #+#             */
/*   Updated: 2025/07/14 10:34:17 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

int	check_i_file_rights(t_chunk *chunk)
{
	int	i;

	i = 0;
	while (i < chunk->redir_file_count)
	{
		if (-1 == access(chunk->input_redir_file[i], R_OK))
		{
			chunk->chunk_exec_return_status_code = 1;
			printf("minishell: %s: %s\n", \
			chunk->input_redir_file[i], strerror(errno));
			return (1);
		}
		i++;
	}
	return (0);
}

int	check_r_file_rights(t_chunk *chunk)
{
	int	i;

	i = 0;
	while (i < chunk->redir_file_count)
	{
		if (-1 == access(chunk->redir_files[i], W_OK))
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
