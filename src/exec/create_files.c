/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 11:26:59 by ofilloux          #+#    #+#             */
/*   Updated: 2025/04/24 14:14:14 by ofilloux         ###   ########.fr       */
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
