/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 15:40:44 by laufarin          #+#    #+#             */
/*   Updated: 2025/06/04 12:03:32 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"
//#include <unistd.h> //BORRAR
//#include <stdlib.h> //BORRAR
//#include<stdio.h> //BORRAR

int	ft_pwd(void)
{
	char	*buff;

	buff = malloc(1024); //tamaño arbitrario
	if (!buff)
	{
		perror("malloc");
		return (1);
	}
	if (getcwd(buff, 1024) == NULL)
	{
		perror("getcwd");
		free(buff);
		return (1);
	}
	printf("%s\n", buff);
	free(buff);
	return (0);
}
/*
int	main()
{
	ft_pwd();
	return (0);
}
*/
