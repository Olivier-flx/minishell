/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_frees.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 11:31:40 by ofilloux          #+#    #+#             */
/*   Updated: 2025/05/07 14:36:28 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

static void free_input_redir(t_chunk **chunk)
{
	if((*chunk)->has_input_redir)
		free_av((*chunk)->input_redir);
	if((*chunk)->input_redir_file_count > 0)
		free_av((*chunk)->input_redir_file);
	if ((*chunk)->input_file_fd_malloced)
		free((*chunk)->input_file_fd);
	if ((*chunk)->input_file_open_malloced)
		free((*chunk)->input_file_open);
}

static void	free_redir(t_chunk **chunk)
{
	if((*chunk)->has_redir)
		free_av((*chunk)->redir);
	if((*chunk)->redir_file_count > 0)
		free_av((*chunk)->redir_files);
	if ((*chunk)->file_fd_malloced)
		free((*chunk)->file_fd);
	if ((*chunk)->file_open_malloced)
		free((*chunk)->file_open);
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
		// FOR later when inputg redir are implemented
		// if (((t_chunk *)(i_node->content))->has_input_redir)
		// {
		// 	free_av(((t_chunk *)(i_node->content))->input_redir);
		// 	free_av(((t_chunk *)(i_node->content))->input_redir_file);
		// }
		i_node = i_node->next;
	}
	free_list(cmd_list);
}
