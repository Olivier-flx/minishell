/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 16:23:22 by ofilloux          #+#    #+#             */
/*   Updated: 2025/04/07 18:31:14 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./header/minishell.h"


// HOW TO RUN //
// valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=readline.supp -s ./mini

int	process_line(char **line)
{
	printf("process line --> %s\n", *line);
	return (0);
}

int initialize_cmd_list(t_data *data)
{
	t_dlist		*cmd_list;

	cmd_list = malloc(sizeof(t_dlist));
	if (!cmd_list)
		return (printf("Error : Mallo cmd_list\n"),1);
	//cmd_list = NULL;
	cmd_list->content = NULL; //@info :initialize to avoir conditional jump or move depending on uninitialised value
	cmd_list->next = NULL;
	cmd_list->prev = NULL;
	data->cmd_list = cmd_list;
	return (0);
}


int	run_minishell(t_data	*data)
{
	char		*line;

	while (true && data->env)
	{
		line = NULL;
		initialize_cmd_list(data);
		line = readline("minishell> ");
		while (line && !all_quote_closed(line))
			line = c_strjoin(line, readline("dquote> "), '\n');

		//////////////// To include in process line /////////
		// while (line && contains_heredoc(line))// structure for the heredoc @ TODO
		// {
		// 	line = c_strjoin(line, readline("heredoc> "), '\n');
		// 	break ; // structure for the heredoc @ TODO
		// 	// manage cat << EOF | cat << END
		// 	// manage cat<test.txt << EOF
		// }
		////////////////////////////////

		if (line && all_quote_closed(line))
		{
			//////////// Anadir Validation del input /////////
			// fonction de validacion de input
			/////////////////////////////
			create_input_token_v3(line, &data->cmd_list, data);
			// if(check_for_user_input_error(&cmd_list) > 0)
			// {
			// 	free_list(&cmd_list);
			// 	free(line);
			// 	continue ;
			// }
			// process herdocs
			process_line(&line);
		//	add_history(line);
		//	clear_history(); //--> donde ponerlo??

			//free (data->ope_char_i.array); // @TODO, protect free if not malloced
			if (data->token_separators_char_i.size > 0)
				free (data->token_separators_char_i.array);// @TODO, protect free if not malloced
			free(line);
		}

		free_cmdlist(data->cmd_list);
		// else
		// 	continue ;
		break ; // @debug : to remove when more advanced
	}
	return (0);
}

int	main(int ac, char **av, char **env)
{
	t_data	data;

	data.env = env;
	data.cmd_list = NULL;
	data.ope_char_i = (t_int_array) {0}; // @util ?
	data.token_separators_char_i = (t_int_array) {0};

	if (ac == 1 && env && av) // modificcar para arrancar igual si no hay env
		return (run_minishell(&data));
	else
		return (1);
	return (0);
}
