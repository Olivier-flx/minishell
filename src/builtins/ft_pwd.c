/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laufarin <laufarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 15:40:44 by laufarin          #+#    #+#             */
/*   Updated: 2025/03/27 17:52:23 by laufarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"
//#include <unistd.h> //BORRAR
//#include <stdlib.h> //BORRAR
//#include<stdio.h> //BORRAR

int	ft_pwd(void)
{
	char	buff[PATH_MAX];

	if (getcwd(buff, PATH_MAX) == NULL)
	{
		perror("getcwd");
		return (1);
	}
	printf("%s\n", buff);
	return (0);
}

int	main(void)
{
	if (ft_pwd() != 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

