/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laufarin <laufarin@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 16:41:01 by laufarin          #+#    #+#             */
/*   Updated: 2024/06/07 14:55:15 by laufarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>

char	*update_storage(char *storage)
{
	char	*new_storage;
	int		i;
	int		j;

	i = 0;
	while (storage[i] != '\n' && storage[i] != '\0')
		i++;
	if (!storage[i])
	{
		return (free(storage), NULL);
	}
	i++;
	new_storage = malloc(sizeof (char) * ft_strlen(storage) - i + 1);
	if (!new_storage)
		return (free(storage), NULL);
	j = 0;
	while (storage[i])
	{
		new_storage[j] = storage[i];
		j++;
		i++;
	}
	new_storage[j] = '\0';
	return (free(storage), new_storage);
}

int	test(char *line, char *storage, int i)
{
	while (storage[i] != '\n' && storage[i] != '\0')
	{
		line[i] = storage[i];
		i++;
	}
	return (i);
}

char	*extract_line(char *storage)
{
	char	*line;
	int		i;

	i = 0;
	if (storage[0] == '\0')
		return (NULL);
	while (storage[i] != '\n' && storage[i] != '\0')
		i++;
	if (storage[i] == '\n')
		i++;
	line = malloc(sizeof (char) * i + 1);
	if (!line)
		return (NULL);
	i = 0;
	i = test(line, storage, i);
	if (storage[i] == '\n')
	{
		line[i] = storage[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*fill_storage(int fd, char *storage)
{
	char	*buffer;
	int		num_bits;

	buffer = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buffer)
	{
		free(storage);
		return (NULL);
	}
	buffer[0] = '\0';
	num_bits = 1;
	while (num_bits > 0 && !ft_strchr(buffer, '\n'))
	{
		num_bits = read(fd, buffer, BUFFER_SIZE);
		if (num_bits == -1)
		{
			return (free(storage), free(buffer), NULL);
		}
		buffer[num_bits] = '\0';
		storage = ft_strjoin_gn(storage, buffer);
	}
	free(buffer);
	return (storage);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*storage[OPEN_MAX];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!storage[fd] || (storage[fd] && !ft_strchr(storage[fd], '\n')))
		storage[fd] = fill_storage(fd, storage[fd]);
	if (!storage[fd])
		return (NULL);
	line = extract_line(storage[fd]);
	if (!line)
	{
		free(storage[fd]);
		storage[fd] = NULL;
		return (NULL);
	}
	storage[fd] = update_storage(storage[fd]);
	return (line);
}
