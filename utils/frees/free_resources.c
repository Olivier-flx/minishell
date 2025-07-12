/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_resources.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 19:22:36 by ofilloux          #+#    #+#             */
/*   Updated: 2025/07/12 15:58:11 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

static void	free_input_redir(t_chunk *chunk)
{
	if (chunk->has_input_redir)
		free_av(&chunk->input_redir);
	close_files_if_opened(chunk->input_file_fd, \
		chunk->input_file_open, chunk->input_redir_count);
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
		close_files_if_opened(chunk->file_fd, chunk->file_open, \
			chunk->redir_count);
		free_av(&chunk->redir_files);
	}
	if (chunk->file_fd_malloced)
		ft_free((void **) &chunk->file_fd);
	if (chunk->file_open_malloced)
		ft_free((void **) &chunk->file_open);
}

void	free_cmdlist(t_dlist *cmd_list)
{
	t_dlist	*i_n;

	i_n = cmd_list;
	while (i_n)
	{
		if ((t_chunk *)(i_n->content))
		{
			if (((t_chunk *)(i_n->content))->tokens)
				free_av(&((t_chunk *)(i_n->content))->tokens);
			if (((t_chunk *)(i_n->content))->argv)
				free_av(&((t_chunk *)(i_n->content))->argv);
			if (((t_chunk *)(i_n->content))->av_0_nopath)
				ft_free((void **) &(((t_chunk *) i_n->content)->av_0_nopath));
			ft_free((void **) &(((t_chunk *) i_n->content)->bin_path));
			ft_free((void **) &(((t_chunk *) i_n->content)->exec));
			free_redir((t_chunk *)(i_n->content));
			free_input_redir((t_chunk *)(i_n->content));
			ft_free((void **) &(i_n->content));
		}
		i_n = i_n->next;
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
	if (data && data->cmd_list)
	{
		free_cmdlist(data->cmd_list);
		clean_exe_nfo(data);
	}
	if (clear_env)
	{
		ft_free_env(data->env_list);
		rl_clear_history();
	}
}
