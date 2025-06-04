/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_resources.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 19:22:36 by ofilloux          #+#    #+#             */
/*   Updated: 2025/06/04 12:03:32 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

static void free_input_redir(t_chunk *chunk)
{
	if (chunk->has_input_redir)
		free_av(&chunk->input_redir);
	close_files_if_opened(chunk->input_file_fd, chunk->input_file_open, chunk->input_redir_count);
	if (chunk->input_redir_file_count > 0)
		free_av(&chunk->input_redir_file);
	if (chunk->input_file_fd_malloced)
		ft_free((void **) &chunk->input_file_fd);
	if (chunk->input_file_open_malloced)
		ft_free((void **) &chunk->input_file_open);
}

static void	free_redir(t_chunk *chunk)
{
	if (chunk->has_redir)
		free_av(&chunk->redir);
	if (chunk->redir_file_count > 0)
	{
		close_files_if_opened(chunk->file_fd, chunk->file_open, chunk->redir_count);
		free_av(&chunk->redir_files);
	}
	if (chunk->file_fd_malloced)
		ft_free((void **) &chunk->file_fd);
	if (chunk->file_open_malloced)
		ft_free((void **) &chunk->file_open);
}

void	free_cmdlist(t_dlist *cmd_list)
{
	t_dlist	*i_node;

	i_node = cmd_list;
	while (i_node)
	{
		if ((t_chunk *)(i_node->content))
		{
			if (((t_chunk *)(i_node->content))->tokens)
				free_av(&((t_chunk *)(i_node->content))->tokens);
			if (((t_chunk *)(i_node->content))->argv)
				free_av(&((t_chunk *)(i_node->content))->argv);
			if (((t_chunk *)(i_node->content))->argv_0_nopath)
				free(((t_chunk *)(i_node->content))->argv_0_nopath);
			free_redir((t_chunk *)(i_node->content));
			free_input_redir((t_chunk *)(i_node->content));
			free((t_chunk *)(i_node->content));
		}
		i_node = i_node->next;
	}
	free_list(cmd_list);
}

void	free_resources(t_data *data, bool clear_env, bool free_line)
{
	if (data)
	{
		ft_free((void **)&data->tok_sep_char_i.array);
		data->tok_sep_char_i.size = 0;
		if (free_line)
			ft_free((void **)&data->line);
	}
	if (data->cmd_list)
	{
		free_cmdlist(data->cmd_list);
		clean_exec_info(data, EXIT_SUCCESS); // @util ?
	}
	if (clear_env)
	{
		ft_free_env(data->env_list);
		rl_clear_history();
	}
}
