/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 15:17:51 by marvin            #+#    #+#             */
/*   Updated: 2025/04/24 15:17:51 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int create_files(t_data *data)
{
	printf("getenv pwd = `%s`\n", ft_getenv(data->env_list,"PWD"));
	//get pwd
	// loop over i_node to get the files
	return(SUCCESS);
}