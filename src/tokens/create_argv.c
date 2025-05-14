/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_argv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 15:26:29 by ofilloux          #+#    #+#             */
/*   Updated: 2025/05/14 16:09:58 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

static int	calculate_len_argv(t_chunk *chunk)
{
	int	len_argv;

	len_argv = 0;
	len_argv = pp_char_len(chunk->tokens) \
				- (chunk->redir_count + count_redir_files_in_chunks(chunk->tokens))
				- (chunk->input_redir_count \
					+ count_input_files_in_chunks(chunk->tokens));
	return (len_argv);
}

void	init_argv(t_chunk *chunk)
{
	int	len_argv;

	if (!chunk)
		return ;
	len_argv = calculate_len_argv(chunk);
	if (len_argv <= 0)
	{
		chunk->argv = NULL;
		return ;
	}
	chunk->argv = malloc(sizeof(char *) * (len_argv + 1));
	if (NULL == chunk->argv)
	{
		printf("Malloc error : al asignar el argv\n");
		return ;// @confirm
	}
	chunk->argv[len_argv] = NULL;
}

static void	set_i_redir_and_bool(int *i_redir, bool *has_redir)
{
	*i_redir += 1;
	*has_redir = true;
}

static void handle_redir(t_chunk *chunk, int *i, int *i_redir)
{
	t_quote	quote;

	init_quotes(&quote);
	if (is_redirection(chunk->tokens[*i], 0, &quote) > 0) // @info: fil the t_chunk redir file with the corresponding redirections
	{
		chunk->redir[*i_redir] = ft_strdup(chunk->tokens[*i]);
		if (chunk->tokens[(*i) + 1] && chunk->redir_files)
			chunk->redir_files[*i_redir] = ft_strdup(chunk->tokens[++(*i)]);
		else
			printf("Error: No file name after a redir\n"); // @debug : error que gestionar despues en user validation function
		set_i_redir_and_bool(i_redir, &chunk->has_redir);
	}
}


void	separate_arg_and_operator(t_chunk *chunk, int i, int i_redir, int i_in_redir)
{
	int	i_argv;
	t_quote	quote;

	init_quotes(&quote);
	i_argv = 0;
	while (chunk->tokens[++i])
	{
		handle_redir(chunk, &i, &i_redir);
/* 		if (is_redirection(chunk->tokens[i], 0, &quote) > 0) // @info: fil the t_chunk redir file with the corresponding redirections
		{
			chunk->redir[i_redir] = ft_strdup(chunk->tokens[i]);
			if (chunk->tokens[i + 1] && chunk->redir_files)
				chunk->redir_files[i_redir] = ft_strdup(chunk->tokens[++i]);
			else
				printf("Error: No file name after a redir\n"); // @debug : error que gestionar despues en user validation function
			set_i_redir_and_bool(&i_redir, &chunk->has_redir);
		}
		else */if (is_input_redir(chunk->tokens[i], 0, &quote) > 0)
		{
			chunk->input_redir[i_in_redir] = ft_strdup(chunk->tokens[i]);
			if (chunk->tokens[i + 1] && chunk->input_redir_file)
				chunk->input_redir_file[i_in_redir] = ft_strdup(chunk->tokens[++i]);
			else
				printf("Error: No file name after a input redir or no EOL\n"); // @debug : error que gestionar despues en user validation function
			set_i_redir_and_bool(&i_in_redir, &chunk->has_input_redir);
		}
		else
			chunk->argv[i_argv++] = ft_strdup(chunk->tokens[i]);
	}
}

int	create_argvs(t_dlist **cmd_list)
{
	t_dlist	*i_node;
	t_chunk	*chunk;

	i_node = *cmd_list;
	while (i_node)
	{
		chunk = (t_chunk *)i_node->content;
		init_redir_arr_and_files(chunk);
		init_input_redir_arr_and_files(chunk);
		init_argv(chunk);
		separate_arg_and_operator(chunk, -1, 0, 0);
		i_node = i_node->next;
	}
	return (EXIT_SUCCESS);
}
