/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_frees.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 11:31:40 by ofilloux          #+#    #+#             */
/*   Updated: 2025/05/11 19:34:14 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	ft_free(void ** ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

void free_pipes_arr(int **pipe_arr, t_exe *exec_info)
{
	int i;

	i = 0;
	while (i < exec_info->total_cmd_count - 1 && exec_info->pipes_malloced[i])
	{
		ft_free((void **) &pipe_arr[i]);
		i++;
	}
	ft_free((void **) &pipe_arr);
	pipe_arr = NULL;
}
