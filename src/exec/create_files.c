/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
<<<<<<<< HEAD:libs/libft/ft_strjoin3.c
/*   ft_strjoin3.c                                      :+:      :+:    :+:   */
========
/*   create_files.c                                     :+:      :+:    :+:   */
>>>>>>>> upstream/dev/exec:src/exec/create_files.c
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
<<<<<<<< HEAD:libs/libft/ft_strjoin3.c
/*   Created: 2025/04/21 19:06:10 by marvin            #+#    #+#             */
/*   Updated: 2025/04/21 19:06:10 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char    *ft_strjoin3(char const*s1, char const*s2, char const*s3)
{
    char    *tmp;
    char    *result;

    tmp = ft_strjoin(s1, s2);
    result = ft_strjoin(tmp, s3);
    free(tmp);
    return(result);

}
========
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
>>>>>>>> upstream/dev/exec:src/exec/create_files.c
