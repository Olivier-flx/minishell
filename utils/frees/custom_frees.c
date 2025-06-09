/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_frees.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 11:31:40 by ofilloux          #+#    #+#             */
/*   Updated: 2025/06/09 21:02:21 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	ft_free(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

void	free_pipes_arr(int **pipe_arr, t_exe *exe_nfo)
{
	int	i;

	i = 0;
	if (!exe_nfo || !exe_nfo->pipes_malloced)
		return ;
	while (i < exe_nfo->total_cmd_count - 1 && exe_nfo->pipes_malloced[i])
	{
		ft_free((void **) &pipe_arr[i]);
		i++;
	}
	ft_free((void **) &pipe_arr);
	pipe_arr = NULL;
}
