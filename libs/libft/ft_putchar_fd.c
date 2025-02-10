/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laufarin <laufarin@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 00:05:24 by laufarin          #+#    #+#             */
/*   Updated: 2023/09/25 00:43:08 by laufarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putchar_fd(char c, int fd)
{
	write (fd, &c, 1);
}

/*int main(void)
{

	char	h;
	int		fd;
	char	archivo[] = "hola.tx";
	int		loop = 10;

	fd = open(archivo, O_WRONLY); 
	h = 'a';
	while (loop > 0)
	{
		ft_putchar_fd(h, fd);
		loop--;
	}
	close(fd);
	return (0);
}*/
