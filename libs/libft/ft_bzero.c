/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laufarin <laufarin@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 21:24:07 by laufarin          #+#    #+#             */
/*   Updated: 2023/09/22 15:25:02 by laufarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*ptr;

	ptr = s;
	i = 0;
	while (i < n)
	{
		ptr[i] = '\0';
		i++;
	}
}

/*int main()*/
/*{
  void *s;
  unsigned char *ptr;

  int i;
  i = 0;
  s = malloc(sizeof(char) * 30);
  ptr = s;
  while (i < 30)
  {
  ptr[i] = 'b';
  i++;
  }
  ft_bzero(s, 10);*/
/*printf("aqui no priuntara nada porque tengo
  10 caracter nulos  |%s|\n", ptr);*/
/*printf("Pero en la posicion 11 
  si que tengo mis b, |%c|\n", ptr[11]);
  ptr[29] = '\0';*/
/*printf("Aqui esta lo que hay detras de los 10
  caracter nulos |%s|\n", &ptr[11]);
  }*/
