/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_frees.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 11:31:40 by ofilloux          #+#    #+#             */
/*   Updated: 2025/04/09 17:03:28 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	free_cmdlist(t_dlist *cmd_list)
{
	t_dlist	*i_node;
	int i = 0; // @debug

	i_node = cmd_list;
	printf("entra\n");
	while (i_node)
	{
		printf("frre num %i ; inode_pointer :  %p\n", i++, i_node);
		if((t_chunk *)(i_node->content))
		{

			free_av(((t_chunk *)(i_node->content))->content);
			free_av(((t_chunk *)(i_node->content))->argv);
			if(((t_chunk *)(i_node->content))->has_redir)
			{
				free_av(((t_chunk *)(i_node->content))->redir);
				free_av(((t_chunk *)(i_node->content))->redir_files);
			}
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
