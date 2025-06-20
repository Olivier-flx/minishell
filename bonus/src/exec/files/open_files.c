/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarodrig <sarodrig@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 18:16:32 by ofilloux          #+#    #+#             */
/*   Updated: 2025/06/11 17:51:09 by sarodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

int	open_redir_file(t_chunk *chunk, int file)
{
	int	fd;

	fd = -1;
	if (ft_strcmp(">", chunk->redir[file]) == 0)
		fd = open(chunk->redir_files[file], \
						O_WRONLY | O_CREAT | O_TRUNC, \
						S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH); // @optimize, mirrar por las autorizaciones antes
	else
		fd = open(chunk->redir_files[file], \
						O_WRONLY | O_CREAT | O_APPEND, \
						S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH); // @optimize, mirrar por las autorizaciones antes
	return (fd);
}
