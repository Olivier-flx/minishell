/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_input_files.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 18:15:17 by ofilloux          #+#    #+#             */
/*   Updated: 2025/06/04 11:54:24 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

/**
 * malloc_fd_arr - Allocates and initializes an array of file descriptors.
 * @chunk: Pointer to the chunk structure where the file_fd array will be stored.
 *
 * This function allocates memory for an array of integers to store file descriptors,
 * based on the redirection count specified in the chunk.
 * It sets the file_fd_malloced flag to true if the allocation succeeds.
 * Each file descriptor is initialized to -1 to indicate that it is unused.
 *
 * Returns:
 *   0 on success,
 *   1 if memory allocation fails.
 */
static int	malloc_input_fd_arr(t_chunk *chunk)
{
	int	i;

	i = 0;
	chunk->input_file_fd_malloced = false;
	if (!chunk->input_redir)
		return (0);
	chunk->input_file_fd = NULL;
	chunk->input_file_fd = malloc(sizeof(int) * chunk->input_redir_count);
	if (!chunk->input_file_fd)
		return (1);
	chunk->input_file_fd_malloced = true;
	while (i < chunk->input_redir_count)
		chunk->input_file_fd[i++] = -1;
	return (0);
}

/**
 * malloc_file_open - Allocates and initializes an array of open file flags.
 * @chunk: Pointer to the chunk structure where the file_open array will be stored.
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
static int	malloc_input_file_open(t_chunk *chunk)
{
	int	i;

	i = 0;
	chunk->input_file_open_malloced = false;
	if (!chunk->input_redir)
		return (0);
	chunk->input_file_open = malloc(sizeof(int) * chunk->input_redir_count);
	if (!chunk->input_file_open )
		return (1);
	chunk->input_file_open_malloced = true;
	while (i < chunk->input_redir_count)
		chunk->input_file_open[i++] = false;
	return (0);
}

int init_input_files(t_data *data)
{
	t_dlist	*i_node;

	i_node = data->cmd_list;
	while(i_node)
	{
		if (malloc_input_fd_arr((t_chunk *)i_node->content) == 1)
			return (printf("Malloc Error : init_files malloc_fd_arr\n"));
		if (malloc_input_file_open((t_chunk *)i_node->content) == 1)
			return (printf("Malloc Error : init_files malloc_file_open\n"));
		//create_files((t_chunk *)i_node->content);
		i_node = i_node->next;
	}
	return (EXIT_SUCCESS);
}
