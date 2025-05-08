/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 10:30:25 by ofilloux          #+#    #+#             */
/*   Updated: 2025/05/08 11:53:53 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"


int main_exec(t_data *data)
{
	//t_dlist *i_node;

	//expend_all(data);
	init_files(data); // OK for now
	init_cmd(data);

	clean_cmds_exit(data, EXIT_SUCCESS, data->exec_info.cmd_err_msg);

	/* i_node = data->cmd_list;
	while (i_node)
	{
		ft_echo(data->env_list, ((t_chunk *)(i_node->content))->argv);
		i_node = i_node->next;
	} */
	return(SUCCESS);
}
