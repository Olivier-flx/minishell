/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 17:06:53 by ofilloux          #+#    #+#             */
/*   Updated: 2025/07/14 10:29:14 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

static int	get_last_redir_index(char **input_redir)
{
	int	i;

	i = 0;
	if (!input_redir)
		return (-1);
	while (input_redir[i])
		i++;
	return (i - 1);
}

static void	heredoc_handler(t_chunk *chunk, int i, int *herdoc_i, int lst_redir)
{
	if (ft_strcmp(chunk->input_redir[i], "<<") == 0)
	{
		if (i == lst_redir && dup2(chunk->heredoc_pipe_arr[*herdoc_i][0], \
				STDIN_FILENO) == -1)
			perror("Minishell : dup2 :");
		close(chunk->heredoc_pipe_arr[*herdoc_i][0]);
		(*herdoc_i)++;
	}
}

static void	redirect_handler(t_chunk *chunk, int i, int lst_redir)
{
	if (ft_strcmp(chunk->input_redir[i], "<") == 0)
	{
		chunk->input_file_fd[i] = open(chunk->input_redir_file[i], O_RDONLY);
		if (chunk->input_file_fd[i] < 0)
		{
			chunk->chunk_exec_return_status_code = errno;
			printf("minishell: %s: %s\n", chunk->input_redir_file[i], \
				strerror(errno));
		}
		chunk->input_file_open[i] = true;
		if (i == lst_redir && dup2(chunk->input_file_fd[i], STDIN_FILENO) == -1)
			strerror(errno);
		if (chunk->input_file_fd[i] >= 0 && close(chunk->input_file_fd[i]) == 0)
			chunk->input_file_open[i] = false;
	}
}

void	redirect_input_file(t_data *data, t_chunk *chunk)
{
	int	i;
	int	lst_redir;
	int	herdoc_i;

	if (!data || !chunk || !chunk->input_redir)
		return ;
	init_i_j(&i, &herdoc_i);
	lst_redir = get_last_redir_index(chunk->input_redir);
	while (chunk->input_redir[i])
	{
		redirect_handler(chunk, i, lst_redir);
		heredoc_handler(chunk, i, &herdoc_i, lst_redir);
		i++;
	}
	if (chunk->heredoc_pipe_arr_malloced)
		ft_free((void **) &chunk->heredoc_pipe_arr);
}

void	redirect_to_output_file(t_data *data, t_chunk *chunk)
{
	int	lst_file;

	if (!data || chunk->redir_file_count == 0)
		return ;
	if (check_r_file_rights(chunk) == 1)
		return ;
	lst_file = chunk->redir_file_count - 1;
	chunk->file_fd[lst_file] = open_redir_file(chunk, lst_file);
	if (chunk->file_fd[lst_file] < 0)
	{
		ft_putstr_fd("Error open(), last file\n", STDERR_FILENO);
		return ;
	}
	chunk->file_open[lst_file] = true;
	if (dup2(chunk->file_fd[lst_file], STDOUT_FILENO) == -1)
		perror("dup2");
	close(chunk->file_fd[lst_file]);
	chunk->file_open[lst_file] = false;
	chunk->file_fd[lst_file] = -1;
}
