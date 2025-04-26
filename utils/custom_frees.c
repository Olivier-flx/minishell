/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_frees.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 11:31:40 by ofilloux          #+#    #+#             */
/*   Updated: 2025/04/26 19:06:06 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

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
			if(((t_chunk *)(i_node->content))->has_redir)
				free_av(((t_chunk *)(i_node->content))->redir);
			if(((t_chunk *)(i_node->content))->redir_file_count > 0)
				free_av(((t_chunk *)(i_node->content))->redir_files);
			if (((t_chunk *)(i_node->content))->file_fd_malloced)
				free(((t_chunk *)(i_node->content))->file_fd);
			if (((t_chunk *)(i_node->content))->file_open_malloced)
				free(((t_chunk *)(i_node->content))->file_open);
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
