/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 11:26:59 by ofilloux          #+#    #+#             */
/*   Updated: 2025/06/14 15:32:41 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

/**
 * malloc_fd_arr - Allocates and initializes an array of file descriptors.
 * @chunk: Pointer to the chunk structure where the file_fd array will be stored.
 *
 * This function allocates memory for an array of integers
 * to store file descriptors,
 * based on the redirection count specified in the chunk.
 * It sets the file_fd_malloced flag to true if the allocation succeeds.
 * Each file descriptor is initialized to -1 to indicate that it is unused.
 *
 * Returns:
 *   0 on success,
 *   1 if memory allocation fails.
 */
static int	malloc_fd_arr(t_chunk *chunk)
{
	int	i;

	chunk->file_fd_malloced = false;
	if (!chunk->redir)
		return (0);
	chunk->file_fd = malloc(sizeof(int) * chunk->redir_count);
	if (!chunk->file_fd)
		return (1);
	chunk->file_fd_malloced = true;
	i = 0;
	while (i < chunk->redir_count)
		chunk->file_fd[i++] = -1;
	return (0);
}

/**
 * malloc_file_open - Allocates and initializes an array of open file flags.
 * @chunk: Pointer to the chunk structure where the
 * file_open array will be stored.
 *
 * This function allocates memory for an array of integers (used as booleans)
 * to track whether each file is successfully opened.
 * It sets the file_open_malloced flag to true if the allocation succeeds.
 * Each element is initialized to 'false' (0).
 *
 * Returns:
 *   0 on success,
 *   1 if memory allocation fails.
 */
static int	malloc_file_open(t_chunk *chunk)
{
	int	i;

	i = 0;
	chunk->file_open_malloced = false;
	if (!chunk->redir)
		return (0);
	chunk->file_open = malloc(sizeof(int) * chunk->redir_count);
	if (!chunk->file_open)
		return (1);
	chunk->file_open_malloced = true;
	while (i < chunk->redir_count)
		chunk->file_open[i++] = false;
	return (0);
}

static int	create_files(t_chunk *chunk)
{
	int	i;

	if (!chunk->redir || !chunk->redir_files)
		return (0);
	i = 0;
	while (chunk->redir[i] && chunk->redir_files[i])
	{
		chunk->file_fd[i] = open_redir_file(chunk, i);
		if (chunk->file_fd[i] < 0)
		{
			chunk->file_open[i] = false;
			return (close_files(chunk), perror("Error : file couldn't open"), \
				EXIT_FAILURE);
		}
		chunk->file_open[i] = true;
		i++;
	}
	close_files(chunk);
	return (0);
}

int	init_files(t_data *data)
{
	t_dlist	*i_node;

	i_node = data->cmd_list;
	while (i_node)
	{
		if (malloc_fd_arr((t_chunk *)i_node->content) == 1)
			return (printf("Malloc Error : init_files malloc_fd_arr\n"));
		if (malloc_file_open((t_chunk *)i_node->content) == 1)
			return (printf("Malloc Error : init_files malloc_file_open\n"));
		create_files((t_chunk *)i_node->content);
		i_node = i_node->next;
	}
	return (EXIT_SUCCESS);
}
