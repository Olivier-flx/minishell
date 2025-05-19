/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_file_arr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 15:29:49 by ofilloux          #+#    #+#             */
/*   Updated: 2025/05/19 16:53:02 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

/**
 * @brief Initializes redirection arrays and associated files for a chunk.
 *
 * This function counts the number of redirection operators in the chunk's content,
 * allocates memory for the redirection arrays and associated files,
 * and initializes the corresponding pointers.
 *
 * @param chunk Pointer to the t_chunk structure to be initialized.
 *
 * @details The function performs the following operations:
 * 1. Counts the number of redirection operators in the chunk's content.
 * 2. If redirection operators are present, allocates memory for the redirection array.
 * 3. Allocates memory for the files associated with the redirections.
 * 4. Initializes the end pointers of the arrays to NULL.
 *
 * @note If memory allocation fails, the function returns immediately.
 *
 * @see count_operador_from_pp_char, count_redir_files_in_chunks
 */
void	init_redir_arr_and_files(t_chunk *chunk)
{
	if (!chunk)
		printf("Error: init_redir_arr_and_files - No chunk\n"); // @debug
	chunk->redir_count = count_redir_from_pp_char(chunk->tokens);
	if (chunk->redir_count > 0)
		chunk->has_redir = true;
	else
	{
		chunk->has_redir = false;
		return ;
	}
	chunk->redir = malloc(sizeof(char *) * (chunk->redir_count + 1));
	if (!chunk->redir)
		return ; // @confirm
	chunk->redir[chunk->redir_count] = NULL;
	chunk->redir_file_count = count_redir_files_in_chunks(chunk->tokens);
	if ( chunk->redir_file_count == 0)
		return ;
	chunk->redir_files = malloc(sizeof(char *) * (chunk->redir_file_count + 1));
	if (!chunk->redir_files)
		return ; // @confirm
	chunk->redir_files[chunk->redir_file_count] = NULL;
}

void	init_input_redir_arr_and_files(t_chunk *chunk)
{
	if (!chunk)
		printf("Error: init_input_redir_arr_and_files - No chunk\n"); // @debug
	chunk->input_redir_count = count_input_redir_from_pp_char(chunk->tokens);
	if (chunk->input_redir_count > 0)
		chunk->has_input_redir = true;
	else
	{
		chunk->has_input_redir = false;
		return ;
	}
	chunk->input_redir = malloc(sizeof(char *) * (chunk->input_redir_count + 1));
	if (!chunk->input_redir)
		return ; // @confirm
	chunk->input_redir[chunk->input_redir_count] = NULL;
	chunk->input_redir_file_count = count_input_files_in_chunks(chunk->tokens);
	chunk->nb_heredocs = count_heredocs_in_chunks(chunk->tokens);
	if ( chunk->input_redir_file_count == 0)
		return ;
	chunk->input_redir_file = malloc(sizeof(char *) * (count_input_files_in_chunks(chunk->tokens) + 1));
	if (!chunk->input_redir_file)
		return ; // @confirm
	chunk->input_redir_file[count_input_files_in_chunks(chunk->tokens)] = NULL;
	chunk->has_here_doc = has_heredoc_from_pp_char(chunk->tokens);
}
