/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pipe_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 13:32:44 by ofilloux          #+#    #+#             */
/*   Updated: 2025/06/04 13:33:11 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

bool	is_pipe_chunk(t_chunk *chunk)
{
	return (chunk && chunk->tokens \
		&& chunk->tokens[0] \
		&& chunk->tokens[0][0] == '|' \
		&& chunk->tokens[0][1] == '\0');
}
