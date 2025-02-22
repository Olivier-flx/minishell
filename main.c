/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 16:23:22 by ofilloux          #+#    #+#             */
/*   Updated: 2025/02/21 17:01:02 by ofilloux         ###   ########.fr       */
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

int	run_minishell(t_data	*data)
{
	char		*line;
	t_dlist		*cmd_list;

	line = NULL;
	cmd_list = malloc(sizeof(t_dlist));
	if (!cmd_list)
		return (1);
	while (true && data->env)
	{
		line = readline("minishell> ");
		while (line && !all_quote_closed(line))
			line = c_strjoin(line, readline("dquote> "), '\n');
		while (true)// structure for the heredoc @ TODO
			break ; // structure for the heredoc @ TODO
		if (line && all_quote_closed(line))
		{
		//	add_history(line);
			create_input_to_commands(line, &cmd_list, data);
			process_line(&line);
		//	clear_history(); //--> donde ponerlo??
			free(line);
		}

		else
			continue ;
		break ; // to remove when more advanced
	}
	free(cmd_list);
	return (0);
}

int	main(int ac, char **av, char **env)
{
	t_data	data;

	data.env = env;
	data.input = NULL;
	data.ope_char_i = (t_int_array) {0};

	if (ac == 1 && env && av) // modificcar para arrancar igual si no hay env
		return (run_minishell(&data));
	else
		return (1);
	return (0);
}
