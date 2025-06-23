/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_input_validation.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 15:14:36 by ofilloux          #+#    #+#             */
/*   Updated: 2025/06/23 17:07:34 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../header/minishell.h"

// check from the last tocken to the first one
//check for redir puis pipe (check_redir_pipe)
int	check_for_user_input_error(t_data *data, t_dlist **cmd_list)
{
	if (unique_empty_chunk(data, *cmd_list))
		return (3);
	if (check_for_simple(*cmd_list) > 0 \
	|| check_for_triple(cmd_list) > 0 \
	|| check_redir_pipe(cmd_list) > 0 \
	|| check_consecutive_pipes(*cmd_list) > 0 \
	|| check_pipe_is_first(*cmd_list) > 0 \
	|| operator_finishes_chunk(*cmd_list) > 0)
	{
		data->exit_status = 2;
		return (2);
	}
	if (bad_var_substitution(data, *cmd_list))
		return (1);
	if (accolade_not_closed(cmd_list) > 0)
		return (1);
	return (0);
}
