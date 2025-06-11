/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_chunks.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 16:49:47 by ofilloux          #+#    #+#             */
/*   Updated: 2025/06/06 10:49:02 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

static int	create_pipe_chunk(int i, t_dlist **cmd_list)
{
	char			*pipe;
	char			**pipe_to_arr;
	t_chunk			*token;

	token = NULL;
	pipe = ft_strdup("|");
	if (pipe != NULL)
	{
		pipe_to_arr = malloc (2 * sizeof (char *));
		if (!pipe_to_arr)
			return (free(pipe), EXIT_FAILURE);
		pipe_to_arr[0] = pipe;
		pipe_to_arr[1] = NULL;
		token = create_token(&pipe_to_arr, PIPE, i, (t_quote){0});
		return (add_to_list(cmd_list, token), ft_strlen(pipe));
	}
	return (EXIT_SUCCESS);
}

void	handle_chunk_before_pipe(t_data *data, char **tokens, \
		int start, int end)
{
	char		**sub_tokens;
	t_chunk		*chunk;
	t_chk_type	type;

	type = CMD;
	if (start > end)
		return ;
	sub_tokens = dup_pp_char(data, tokens, start, end);
	retocken_after_expension(&sub_tokens);
	if (!sub_tokens)
		return ;
	if (!sub_tokens[0])
		type = EMPTY;
	chunk = create_token(&sub_tokens, type, start, (t_quote){0});
	add_to_list(&data->cmd_list, chunk);
}

void	handle_chunk_after_last_pipe(t_data *data, char **tokens, \
		int start, int end)
{
	char		**sub_tokens;
	t_chunk		*chunk;
	t_chk_type	type;

	type = CMD;
	if (start > end)
		return ;
	sub_tokens = dup_pp_char(data, tokens, start, end);
	retocken_after_expension(&sub_tokens);
	if (!sub_tokens)
		return ;
	if (!sub_tokens[0])
		type = EMPTY;
	chunk = create_token(&sub_tokens, type, start, (t_quote){0});
	add_to_list(&data->cmd_list, chunk);
}

int	create_main_chunks(char *src, t_dlist **cmd_list, t_data *data)
{
	char	**all_tokens;
	int		i;
	int		flag_last_pipe;

	if (!cmd_list)
		return (EXIT_FAILURE);
	i = 0;
	flag_last_pipe = 0;
	all_tokens = split_quoted2(src, data);
	while (all_tokens && all_tokens[i] && all_tokens[i][0])
	{
		if (i > 0 && all_tokens[i][0] == '|')
		{
			handle_chunk_before_pipe(data, all_tokens, flag_last_pipe, i - 1);
			create_pipe_chunk(i, cmd_list);
			flag_last_pipe = i + 1;
		}
		i++;
	}
	handle_chunk_after_last_pipe(data, all_tokens, flag_last_pipe, i - 1);
	free_av(&all_tokens);
	return (EXIT_SUCCESS);
}

int	create_chunks(char *line, t_dlist **cmd_list, t_data *data)
{
	if (! data)
		return (EXIT_FAILURE);
	if (!preliminary_checks_ok(data, line))
		return (EXIT_FAILURE);
	if (create_main_chunks(line, cmd_list, data) > 0)
		return (printf("Error : create_main_chunks"));
	if (check_for_user_input_error(data, cmd_list) != 0)
		return (3);
	if (create_argvs(cmd_list) == 1)
		return (2);
	data->nb_chunks = (int) stack_lenght(cmd_list);
	return (EXIT_SUCCESS);
}
