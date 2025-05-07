/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 10:30:25 by ofilloux          #+#    #+#             */
/*   Updated: 2025/05/07 18:11:13 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"


int main_exec(t_data *data)
{
	t_dlist *i_node;

	//expend_all(data);
	init_files(data); // OK for now
	init_cmd(data);
	i_node = data->cmd_list;
	while (i_node)
	{
		ft_echo(data->env_list, ((t_chunk *)(i_node->content))->argv);
		i_node = i_node->next;
	}
	return(SUCCESS);
}
