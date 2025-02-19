/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 16:23:22 by ofilloux          #+#    #+#             */
/*   Updated: 2025/02/19 17:21:57 by ofilloux         ###   ########.fr       */
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
	char		*tmp;
	t_dlist		*cmd_list;

	tmp = NULL;
	line = NULL;
	cmd_list = malloc(sizeof(t_dlist));
	if (!cmd_list)
		return (1);
	while (true && data->env)
	{
		line = readline("minishell> ");
		while (line && !all_quote_closed(line))
			line = c_strjoin(line, readline("dquote> "), '\n');
		if (line && all_quote_closed(line))
		{
			create_input_to_commands(line, &cmd_list, data);
		//	add_history(line);
		//	clear_history();
			process_line(&line);
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
