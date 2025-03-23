/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_tockens_v2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 16:49:47 by ofilloux          #+#    #+#             */
/*   Updated: 2025/03/19 21:49:40 by ofilloux         ###   ########.fr       */
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

void	create_main_chunks(char *src, t_dlist **cmd_list)
{
	char	**all_tokens;
	char	**chunk;
	t_chunk	*token;
	int		i;
	int		flag_last_pipe;

	i = 0;
	flag_last_pipe = 0;
	all_tokens = split_quoted(src, ' ');
	print_pp_char_arr(all_tokens);
	while (all_tokens && all_tokens[i] && all_tokens[i][0])
	{
		if (all_tokens[i][0] == '|')
		{
			chunk = dup_pp_char(all_tokens, flag_last_pipe, i - 1 );
			token = create_token(&chunk, CMD, i, (t_quote) {0}); // i correspond au numéro du chunk / index du chunk dans la string. à retirer
			add_to_list(cmd_list, token);
			create_pipe_chunk(i, cmd_list);
			flag_last_pipe = i + 1;
		}
		i++;
	}
	chunk = dup_pp_char(all_tokens, flag_last_pipe, i - 1 );
	token = create_token(&chunk, CMD, i, (t_quote) {0}); // i correspond au numéro du chunk / index du chunk dans la string. à retirer
	add_to_list(cmd_list, token);
	free(all_tokens);

	printf("la list est ici ->\n");
	print_dlist(cmd_list);
}

void	init_redir_arr_and_files(t_chunk chunk)
{
	int	redir_count;

	redir_count = count_operador(chunk->content);
	chunk->redir = malloc(sizeof(char *) * (redir_count + 1));
	if (!chunk->redir)
		return (NULL);
	chunk->redir_files = malloc(sizeof(char *) * (redir_count + 1))
}

void	separate_arg_and_operator(t_chunk * chunk)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (chunk->content[i])
	{
		init_redir_arr(chunk);
		if (is_operator(chunk->content[i], 0, t_quote *{0,0}))
		{
			chunk->redir[j] = s_dup(chunk->content[i]);
			if (chunk->content[i + 1])
				chunk->redir[j] = s_dup(chunk->content[++i]);
			else
				printf("Error --> No file name after a redir\n");
		}
		else


		printf("`%s`;", chunk->content[i++]);
		fflush(stdout);
		i++;
	}


}

int	create_argvs(t_dlist **cmd_list)
{
	t_dlist	*i_node;

	i_node = cmd_list;

	while (i_node)
	{
		separate_arg_and_operator((t_chunk *)i_node->content)
		i_node = i_node->next;
	}
}

int	create_input_token_v3(char *line,  t_dlist **cmd_list, , t_data *data)
{
	create_main_chunks(line, cmd_list);
	create_argvs(cmd_list);
	printf("la list est ici ->\n");
	print_dlist(cmd_list);
}
