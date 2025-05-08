/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_frees.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 11:31:40 by ofilloux          #+#    #+#             */
/*   Updated: 2025/05/08 15:42:21 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void free_pipes_arr(int **pipe_arr, t_exe *exec_info)
{
	int i;

	i = 0;
	while (i < exec_info->total_cmd_count - 1 && exec_info->pipes_malloced[i])
	{
		free(pipe_arr[i]);
		i++;
	}
	free(pipe_arr);
	pipe_arr = NULL;
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

static void free_input_redir(t_chunk *chunk)
{
	if(chunk->has_input_redir)
		free_av(chunk->input_redir);
	close_files_if_opened(chunk->input_file_fd, chunk->input_file_open);
	if(chunk->input_redir_file_count > 0)
		free_av(chunk->input_redir_file);
	if (chunk->input_file_fd_malloced)
		free(chunk->input_file_fd);
	if (chunk->input_file_open_malloced)
		free(chunk->input_file_open);
}

static void	free_redir(t_chunk *chunk)
{
	if(chunk->has_redir)
		free_av(chunk->redir);
	if(chunk->redir_file_count > 0)
	{
		close_files_if_opened(chunk->file_fd, chunk->file_open);
		free_av(chunk->redir_files);
	}
	if (chunk->file_fd_malloced)
		free(chunk->file_fd);
	if (chunk->file_open_malloced)
		free(chunk->file_open);
}

void	free_cmdlist(t_dlist *cmd_list)
{
	t_dlist	*i_node;

	i_node = cmd_list;
	while (i_node)
	{
		if((t_chunk *)(i_node->content))
		{
			if (((t_chunk *)(i_node->content))->tokens)
				free_av(((t_chunk *)(i_node->content))->tokens);
			if (((t_chunk *)(i_node->content))->argv)
				free_av(((t_chunk *)(i_node->content))->argv);
			free_redir((t_chunk *)(i_node->content));
			free_input_redir((t_chunk *)(i_node->content));
			free((t_chunk *)(i_node->content));
		}
		i_node = i_node->next;
	}
	free_list(cmd_list);
}
