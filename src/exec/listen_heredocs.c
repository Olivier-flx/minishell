/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listen_heredocs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 17:41:15 by ofilloux          #+#    #+#             */
/*   Updated: 2025/05/10 18:09:52 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

//Retourne l'index de char c, ou -1 si pas trouvé
static int string_search(char *s, char c)
{
	int	i;

	i = 0;
	while (s && s[i])
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

//tronque en incluant l'index n
static char	*ft_truncate(char *s, int n)
{
	char	*cpy;
	int		i;
	int		s_len;

	i = 0;
	printf("\n\ns in trincate = %si\n", s);
	if (!s)
		return (NULL);
	s_len = (int) ft_strlen(s);
	printf("\n\ns_len = %i\nn = %i\n", s_len, n);
	if (n > s_len)
		n = s_len;
	cpy = malloc(sizeof(char) * (n + 2)); /// TEST +1 pour \n et +2 avec le null à la fin
	if (!cpy)
		return (NULL);
	while (i <= n)
	{
		cpy[i] = s[i];
		i++;
	}
	cpy[i] = '\0';
	printf("\n\nCpy in trincate = %si\n", cpy);
	return (cpy);
}

// static char *reverse_truncate(char *s, int n)
// {
// 	char	*cpy;
// 	int		i;
// 	int		s_len;
// 	int		cpy_len;

// 	i = 0;
// 	if (!s)
// 		return (NULL);
// 	s_len = ft_strlen(s);
// 	if (n >= s_len)
// 		return (free(s), NULL);
// 	cpy_len = s_len - n;
// 	cpy = malloc(sizeof(char) * (cpy_len + 1));
// 	if (!cpy)
// 		return (NULL);
// 	while (++n < cpy_len)
// 	{
// 		cpy[i] = s[n];
// 		i++;
// 	}
// 	cpy[i] = '\0';
// 	return (cpy);
// }

char	*ft_strcpy(char *src, char *cpy)
{
	int	i;

	if (!src)
		return (NULL);
	i = -1;
	while (src[++i])
		cpy[i] = src[i];
	return (cpy);
}

int	ft_get_line(int fd, char **line)
{
	int		buf_size = 3;
	char	buffer[buf_size];
	int		bytes_readen;
	char	*leftovers;
	char	*tmp;

	leftovers = NULL;
	tmp = NULL;
	if (!line || fd < 0)
		return (-1);

	while (1)
	{

		if (leftovers && leftovers[0] && string_search(leftovers, '\n') >= 0)
		{
			if (*line)
				free(*line);
			*line = ft_truncate(leftovers, string_search(leftovers, '\n'));
			break ;
		}
		printf("fd = %i \n",fd);
		bytes_readen = read(fd, buffer, buf_size - 1);
		if (bytes_readen < 0 && leftovers)// (fichier 100% lu || erreur) && il y a des restes
			return (free(leftovers), -1);
		if (bytes_readen < 0)// fichier 100% lu || erreur && pas de restes
			return (-1);
		buffer[bytes_readen] = '\0';

		*line = ft_strjoin(leftovers, buffer);
		// Cas ou le fichier vient de finir
		if (bytes_readen >=0 && bytes_readen < buf_size - 1)
			break;
		if(ft_strncmp(*line, "limit", 5) == 0)
			break;
		if (string_search(*line, '\n') >= 0)
		{
			tmp = *line;
			*line = ft_truncate(*line, string_search(*line, '\n'));
			free(tmp);
			break ;
		}
		else
		{
			if (leftovers)
				free(leftovers);
			leftovers = ft_strdup(*line);
			free (*line);
		}

	}
	if (leftovers)
		free(leftovers);
	return (string_search(*line, '\n'));
}

/// ////////////////////

int	listen_terminal(char *limiter)
{
	int		pipes[2]; // @confirm Need to try i y need to extract pipe[2] de listen_terminaal pour le mettre  directement dans listen heredoc. J'ai peur qu'en le fermant a la fin de listen terminal je n'arrive pas a ecouter plusieurs heredoc
	char	*line;
	int		limiter_len;
	int		n_index;

	line = NULL;
	limiter_len = (int) ft_strlen(limiter);
	if (pipe(pipes) < 0)
		return (perror("pipe"), 1);
	dup2(pipes[0], STDIN_FILENO);
	close(pipes[0]);
	while (1)
	{
		n_index = ft_get_line(STDIN_FILENO, &line);
		if (n_index < 0 && write(STDERR_FILENO, "Error reading from terminal\n", 29))
			break ;
		if (ft_strncmp(line, limiter, limiter_len) == 0 && (int) ft_strlen(line) - 1 == limiter_len)
		{//LIMITER trouvé et unique sur sa ligne
			close(pipes[1]);
			break ;
		}
		else
		{
			write (pipes[1], line, ft_strlen(line));
			if (line)
				ft_free ((void **) &line);
			line = NULL;
		}
	}
	if (line)
		ft_free ((void **) &line);
	close(pipes[1]);
	if (n_index < 0)
		return(1);
	return (0);
}

int	listen_heredocs(t_chunk *chunk, int i)
{
	while (chunk->input_redir && chunk->input_redir[i])
	{
		if (ft_strcmp("<<", chunk->input_redir[i]) == 0)
			listen_terminal(chunk->input_redir_file[i]);
	}
	return (0);
}
