/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_argv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 15:26:29 by ofilloux          #+#    #+#             */
/*   Updated: 2025/05/14 15:28:05 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

static int	calculate_len_argv (t_chunk *chunk)
{
	int	len_argv;

	len_argv = 0;
	len_argv = pp_char_len(chunk->tokens) \
				- (chunk->redir_count + count_redir_files_in_chunks(chunk->tokens))
				- (chunk->input_redir_count + count_input_files_in_chunks(chunk->tokens));
	return (len_argv);
}

void	init_argv(t_chunk *chunk)
{
	int	len_argv;

	if (!chunk)
		return ;
	//printf("\n---------------\n pp_char_len(chunk->content) = %i\n",pp_char_len(chunk->tokens));// @debug
	len_argv = calculate_len_argv(chunk);
	//printf("init_argv chunk->redir_count = %i\n",chunk->redir_count);// @debug
	//printf("init_argv len_argv = %i\n",len_argv);// @debug

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

void	separate_arg_and_operator(t_chunk *chunk)
{
	int	i;
	int	i_redir;
	int i_in_redir;
	int	i_argv;
	t_quote	quote;

	init_quotes(&quote);

	i = 0;
	i_redir = 0;
	i_in_redir = 0;
	i_argv = 0;
	init_redir_arr_and_files(chunk);
	init_input_redir_arr_and_files(chunk);
	init_argv(chunk);
	//printf("token != operator = "); // @debug
	//fflush(stdout);  // @debug
	while (chunk->tokens[i])
	{
		if (is_redirection(chunk->tokens[i], 0, &quote) > 0) // @info: fil the t_chunk redir file with the corresponding redirections
		{
			chunk->redir[i_redir] = ft_strdup(chunk->tokens[i]);
			if (chunk->tokens[i + 1] && chunk->redir_files)
				chunk->redir_files[i_redir] = ft_strdup(chunk->tokens[++i]);
			else
				printf("Error: No file name after a redir\n"); // @debug : error que gestionar despues en user validation function
			chunk->has_redir = true; // @Util : 2025-03-23, no se si util?
			i_redir++;
		}
		else if (is_input_redir(chunk->tokens[i], 0, &quote) > 0)
		{
			chunk->input_redir[i_in_redir] = ft_strdup(chunk->tokens[i]);
			if (chunk->tokens[i + 1] && chunk->input_redir_file)
				chunk->input_redir_file[i_in_redir] = ft_strdup(chunk->tokens[++i]);
			else
				printf("Error: No file name after a input redir or no EOL\n"); // @debug : error que gestionar despues en user validation function
			chunk->has_input_redir = true; // @Util : 2025-03-23, no se si util?
			i_in_redir++;
		}
		else
			chunk->argv[i_argv++] = ft_strdup(chunk->tokens[i]);
		//printf("`%s`;", chunk->tokens[i]); // @debug
		//fflush(stdout);  // @debug
		i++;
	}
	//printf("\n"); // @debug
}

int	create_argvs(t_dlist **cmd_list)
{
	t_dlist	*i_node;

	i_node = *cmd_list;
	while (i_node)
	{
		separate_arg_and_operator((t_chunk *)i_node->content);
	//////debug
		// printf("argv is :\n");// @debug
		// print_pp_char_arr(((t_chunk *)i_node->content)->argv); // @debug
		// printf("end argv\n\n");// @debug
		// if (((t_chunk *)i_node->content)->redir_count > 0)// @debug
		// {// @debug
		// 	printf("redir is :\n");// @debug
		// 	print_pp_char_arr(((t_chunk *)i_node->content)->redir); // @debug
		// 	print_pp_char_arr(((t_chunk *)i_node->content)->redir_files); //@debug
		// 	printf("end redir\n\n");// @debug
		// }// @debug
	/////////
		i_node = i_node->next;
	}
	return (EXIT_SUCCESS); // @confirm : what value to return if success ? is returning void couldn't be better ?
}
