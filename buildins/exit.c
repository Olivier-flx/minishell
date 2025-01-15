/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 20:37:08 by ofilloux          #+#    #+#             */
/*   Updated: 2025/01/12 20:40:26 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

//return 0 if success
int b_exit(int ret_val, t_data data)
{
	// free all mallocs through data before exiting;
	// dont forget to free "line"
	exit(ret_val);
}
