/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_argv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 15:26:29 by ofilloux          #+#    #+#             */
/*   Updated: 2025/05/19 17:20:48 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

static int	calculate_len_argv(t_chunk *chunk)
{
	int	len_argv;
	int	redir_token_len;
	int	input_redir_token_len;

	len_argv = 0;
	redir_token_len = chunk->redir_count \
		+ count_redir_files_in_chunks(chunk->tokens);
	input_redir_token_len  = chunk->input_redir_count \
					+ count_input_files_in_chunks(chunk->tokens);
	len_argv = pp_char_len(chunk->tokens) \
			- (redir_token_len + input_redir_token_len);
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



void	separate_arg_and_operator(t_chunk *chunk, int i, int i_redir, int i_in_redir)
{
	int	i_argv;
	t_quote	quote;

	init_quotes(&quote);
	i_argv = 0;
	while (chunk->tokens[++i])
	{
		if (handle_redir(chunk, &i, &i_redir) == 1)
			continue ;
		if (handle_input_redir(chunk, &i, &i_redir) == 1)
			continue ;
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
