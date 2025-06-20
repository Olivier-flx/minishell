/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   root.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 19:08:36 by ofilloux          #+#    #+#             */
/*   Updated: 2025/06/20 18:07:56 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

/**
 *  @brief The root of the asterisk extention
 *         used in retocken_after_expension()
 *
 *  @param	str char *string
 */
int	expend_asterisk(t_data *data, char *str)
{
	DIR				*dir_p;
	struct dirent	*entry;

	dir_p = opendir(ft_getenv(data->env, "PWD"));
	if (!dir_p)
		return (perror("opendir"), 1);
	entry = readdir(dir_p);


	printf("desde expend_asterisk `%s`\n", str);
}
