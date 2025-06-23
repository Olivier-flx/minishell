/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunks_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 10:46:57 by ofilloux          #+#    #+#             */
/*   Updated: 2025/06/23 16:54:23 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../header/minishell.h"

bool	chunk_is_empty(t_chunk *chk)
{
	return (!(chk->tokens[0]));
}

bool	unique_empty_node(t_data *data, t_dlist *cmd_list)
{
	t_chunk	*chk;

	chk = ((t_chunk *) cmd_list->content);
	if (!cmd_list->next && chunk_is_empty(chk))
	{
		data->exit_status = 0;
		return (true);
	}
	return (false);
}

