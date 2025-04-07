/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_frees.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 11:31:40 by ofilloux          #+#    #+#             */
/*   Updated: 2025/04/07 18:57:34 by ofilloux         ###   ########.fr       */
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
			free_av(((t_chunk *)(i_node->content))->content);
			free_av(((t_chunk *)(i_node->content))->argv);
		}
		if(((t_chunk *)(i_node->content))->has_redir)
		{
			free_av(((t_chunk *)(i_node->content))->redir);
			free_av(((t_chunk *)(i_node->content))->redir_files);
		}
		// FOR later when inputg redir are implemented
		// if (((t_chunk *)(i_node->content))->has_input_redir)
		// {
		// 	free_av(((t_chunk *)(i_node->content))->input_redir);
		// 	free_av(((t_chunk *)(i_node->content))->input_redir_file);
		// }
		free((t_chunk *)(i_node->content));
		i_node = i_node->next;
	}
	free_list(&cmd_list);
	free(cmd_list);
}
