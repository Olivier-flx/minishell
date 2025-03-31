/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_tockens_v2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 16:49:47 by ofilloux          #+#    #+#             */
/*   Updated: 2025/03/31 19:03:32 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

// char	*pipe_sdup(char *src, int i)
// {
// 	char	*operador;

// 	operador = NULL;
// 	if (src[i] == 124)
// 		operador = s_dup("|");
// 	return (operador);
// }


static int	create_pipe_chunk(int i, t_dlist **cmd_list)
{
	char			*pipe;
	char			**pipe_to_arr;
	t_chunk	*token;

	token = NULL;
	pipe = s_dup("|");;
	if (pipe != NULL)
	{
		pipe_to_arr = malloc (2 * sizeof (char *));
		if (!pipe_to_arr)
			return (free(pipe), 0);
		pipe_to_arr[0] = pipe;
		pipe_to_arr[1] = NULL;
		token = create_token(&pipe_to_arr, PIPE, i, (t_quote) {0});
		return (add_to_list(cmd_list, token), s_len(pipe));
	}
	return (0);
}

int	create_main_chunks(char *src, t_dlist **cmd_list, t_data *data)
{
	char	**all_tokens;
	char	**chunk;
	t_chunk	*token;
	int		i;
	int		flag_last_pipe;

	if (!cmd_list) // @util ?
		return(printf("cmd_list = NULL\n")); // @util ?
	i = 0;
	flag_last_pipe = 0;
	all_tokens = split_quoted2(src, data);
	while (all_tokens && all_tokens[i] && all_tokens[i][0])
	{
		if (all_tokens[i][0] == '|') // @info : Si encuentra '|' crea el chunk de antes y el chunk de '|'
		{
			chunk = dup_pp_char(all_tokens, flag_last_pipe, i - 1 );
			token = create_token(&chunk, CMD, i, (t_quote) {0}); // i correspond au numéro du chunk / index du chunk dans la string. à retirer
			add_to_list(cmd_list, token);
			create_pipe_chunk(i, cmd_list);
			flag_last_pipe = i + 1;
		}
		i++;
	}
	if (i > 0)
		i--;
	if (all_tokens && all_tokens[i] && all_tokens[i][0])// @info : crea el ultimo chunK
	{
		chunk = dup_pp_char(all_tokens, flag_last_pipe, i);
		token = create_token(&chunk, CMD, i, (t_quote) {0}); // i correspond au numéro du chunk / index du chunk dans la string. à retirer
		add_to_list(cmd_list, token);
	}
	free(all_tokens);
	return (0);
}

void	init_redir_arr_and_files(t_chunk *chunk)
{
	chunk->redir_count = count_operador_from_pp_char(chunk->content);
	chunk->redir = malloc(sizeof(char *) * (chunk->redir_count + 1));
	if (!chunk->redir)
		return ; // @confirm
	chunk->redir[chunk->redir_count] = 0;
	chunk->redir_files = malloc(sizeof(char *) * (chunk->redir_count + 1));
	if (!chunk->redir_files)
		return ; // @confirm
	chunk->redir_files[chunk->redir_count] = 0;
}

void	init_argv(t_chunk *chunk)
{
	int	len_argv;

	if (!chunk)
		return ;
	printf("pp_char_len(chunk->content) = %i\n",pp_char_len(chunk->content));
	len_argv = pp_char_len(chunk->content) - (chunk->redir_count * 2); //@info : x2 para redir y et nombre del file
	printf("init_argv chunk->redir_count = %i\n",chunk->redir_count);
	printf("init_argv len_argv = %i\n",len_argv);
	chunk->argv = malloc (sizeof(char *) * (len_argv + 1));
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
	int	i_argv;
	t_quote	quote = {0,0};

	i = 0;
	i_redir = 0;
	i_argv = 0;
	init_redir_arr_and_files(chunk);
	init_argv(chunk);
	printf("token != operator = "); // @debug
	fflush(stdout);  // @debug
	while (chunk->content[i])
	{
		if (is_redirection(chunk->content[i], 0, &quote) > 0) // @info: fil the t_chunk redir file with the corresponding redirections
		{
			chunk->redir[i_redir] = s_dup(chunk->content[i]);
			if (chunk->content[i + 1])
				chunk->redir_files[i_redir] = s_dup(chunk->content[++i]);
			else
				printf("Error --> No file name after a redir\n");
			chunk->has_redir = true; // @Util : 2025-03-23, no se si util?
			i_redir++;
		}
		else
			chunk->argv[i_argv++] = s_dup(chunk->content[i]);
		printf("`%s`;", chunk->content[i]); // @debug
		fflush(stdout);  // @debug
		i++;
	}
	printf("\n"); // @debug
}

int	create_argvs(t_dlist **cmd_list)
{
	t_dlist	*i_node;

	i_node = *cmd_list;

	while (i_node)
	{
		separate_arg_and_operator((t_chunk *)i_node->content);
		printf("argv is :\n");// @debug
		print_pp_char_arr(((t_chunk *)i_node->content)->argv); // @debug
		printf("end argv\n\n");// @debug
		printf("redir is :\n");// @debug
		print_pp_char_arr(((t_chunk *)i_node->content)->redir); // @debug
		print_pp_char_arr(((t_chunk *)i_node->content)->redir_files); //@debug
		printf("end redir\n\n");// @debug
		i_node = i_node->next;
	}
	return (0); // @confirm : what value to return if success ? is returning void couldn't be better ?
}

int	create_input_token_v3(char *line,  t_dlist **cmd_list, t_data *data)
{
	if (! data)
		return(0);
	if (create_main_chunks(line, cmd_list, data) > 0)
		return (printf("Error : create_main_chunks"));
	create_argvs(cmd_list);
	return(0); // @confirm : what value to return if success ? is returning void couldn't be better ?
}
