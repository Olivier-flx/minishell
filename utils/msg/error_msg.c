/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 09:48:20 by ofilloux          #+#    #+#             */
/*   Updated: 2025/01/26 09:49:43 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	simple_error_msg(char *msg)
{
	write(STDERR_FILENO, msg, slen(msg));
	write(STDERR_FILENO, "\n", 1);
}
