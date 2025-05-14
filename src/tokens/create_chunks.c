/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_chunks.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 16:49:47 by ofilloux          #+#    #+#             */
/*   Updated: 2025/05/14 11:41:57 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

static int	create_pipe_chunk(int i, t_dlist **cmd_list)
{
	char			*pipe;
	char			**pipe_to_arr;
	t_chunk			*token;

	token = NULL;
	pipe = ft_strdup("|");;
	if (pipe != NULL)
	{
		pipe_to_arr = malloc (2 * sizeof (char *));
		if (!pipe_to_arr)
			return (free(pipe), EXIT_FAILURE);
		pipe_to_arr[0] = pipe;
		pipe_to_arr[1] = NULL;
		token = create_token(&pipe_to_arr, PIPE, i, (t_quote) {0});
		return (add_to_list(cmd_list, token),ft_strlen(pipe));
	}
	return (EXIT_SUCCESS);
}


int	create_main_chunks(char *src, t_dlist **cmd_list, t_data *data)
{
	char	**all_tokens;
	char	**tokens;
	t_chunk	*chunk;
	int		i;
	int		flag_last_pipe;

	if (!cmd_list) // @util ?
		return(EXIT_FAILURE); // @util ?
	i = 0;
	flag_last_pipe = 0;
	all_tokens = split_quoted2(src, data);
	while (all_tokens && all_tokens[i] && all_tokens[i][0])
	{
		if (i > 0 && all_tokens[i][0] == '|') // @info : Si encuentra '|' crea el chunk de antes y el chunk de '|'
		{
			tokens = dup_pp_char(data, all_tokens, flag_last_pipe, i - 1);
			chunk = create_token(&tokens, CMD, i, (t_quote) {0}); // i correspond au numéro du chunk / index du chunk dans la string. à retirer
			add_to_list(cmd_list, chunk);
			create_pipe_chunk(i, cmd_list);
			flag_last_pipe = i + 1;
		}
		else if (i == 0 && all_tokens[i][0] == '|')
		{
			create_pipe_chunk(i, cmd_list);
			flag_last_pipe = i + 1;
		}

		i++;
	}
	if (i > 0)
		i--;
	if (all_tokens && all_tokens[i] && all_tokens[i][0] && all_tokens[i][0] != '|')// @info : crea el ultimo chunK
	{
		tokens = dup_pp_char(data, all_tokens, flag_last_pipe, i);
		chunk = create_token(&tokens, CMD, i, (t_quote) {0}); // i correspond au numéro du chunk / index du chunk dans la string. à retirer
		add_to_list(cmd_list, chunk);
	}
	free_av(&all_tokens);
	return (EXIT_SUCCESS);
}

/**
 * @brief Initializes redirection arrays and associated files for a chunk.
 *
 * This function counts the number of redirection operators in the chunk's content,
 * allocates memory for the redirection arrays and associated files,
 * and initializes the corresponding pointers.
 *
 * @param chunk Pointer to the t_chunk structure to be initialized.
 *
 * @details The function performs the following operations:
 * 1. Counts the number of redirection operators in the chunk's content.
 * 2. If redirection operators are present, allocates memory for the redirection array.
 * 3. Allocates memory for the files associated with the redirections.
 * 4. Initializes the end pointers of the arrays to NULL.
 *
 * @note If memory allocation fails, the function returns immediately.
 *
 * @see count_operador_from_pp_char, count_redir_files_in_chunks
 */
void	init_redir_arr_and_files(t_chunk *chunk)
{
	if (!chunk)
		printf("Error: init_redir_arr_and_files - No chunk\n"); // @debug
	chunk->redir_count = count_redir_from_pp_char(chunk->tokens);
	if (chunk->redir_count > 0)
		chunk->has_redir = true;
	else
	{
		chunk->has_redir = false;
		return ;
	}
	chunk->redir = malloc(sizeof(char *) * (chunk->redir_count + 1));
	if (!chunk->redir)
		return ; // @confirm
	chunk->redir[chunk->redir_count] = NULL;
	chunk->redir_file_count = count_redir_files_in_chunks(chunk->tokens);
	if ( chunk->redir_file_count == 0)
		return ;
	chunk->redir_files = malloc(sizeof(char *) * (count_redir_files_in_chunks(chunk->tokens) + 1));
	if (!chunk->redir_files)
		return ; // @confirm
	chunk->redir_files[count_redir_files_in_chunks(chunk->tokens)] = NULL;
}

void	init_input_redir_arr_and_files(t_chunk *chunk)
{
	if (!chunk)
		printf("Error: init_input_redir_arr_and_files - No chunk\n"); // @debug
	chunk->input_redir_count = count_input_redir_from_pp_char(chunk->tokens);
	if (chunk->input_redir_count > 0)
		chunk->has_input_redir = true;
	else
	{
		chunk->has_input_redir = false;
		return ;
	}
	chunk->input_redir = malloc(sizeof(char *) * (chunk->input_redir_count + 1));
	if (!chunk->input_redir)
		return ; // @confirm
	chunk->input_redir[chunk->input_redir_count] = NULL;
	chunk->input_redir_file_count = count_input_files_in_chunks(chunk->tokens);
	chunk->nb_heredocs = count_heredocs_in_chunks(chunk->tokens);
	if ( chunk->input_redir_file_count == 0)
		return ;
	chunk->input_redir_file = malloc(sizeof(char *) * (count_input_files_in_chunks(chunk->tokens) + 1));
	if (!chunk->input_redir_file)
		return ; // @confirm
	chunk->input_redir_file[count_input_files_in_chunks(chunk->tokens)] = NULL;
	chunk->has_here_doc = has_heredoc_from_pp_char(chunk->tokens);
}

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

int	create_chunks(char *line,  t_dlist **cmd_list, t_data *data)
{
	if (! data)
		return(EXIT_FAILURE);
	if (!preliminary_checks_ok(data, line))
		return(EXIT_FAILURE);
	if (create_main_chunks(line, cmd_list, data) > 0)
		return (printf("Error : create_main_chunks"));
	if (check_for_user_input_error(data, cmd_list) != 0)
		return (3);
	if (create_argvs(cmd_list) == 1) // if error retrun 1
		return (2);
	data->nb_chunks = (int) stack_lenght(cmd_list);
	return(EXIT_SUCCESS); // @confirm : what value to return if success ? is returning void couldn't be better ?
}
