/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 16:23:22 by ofilloux          #+#    #+#             */
/*   Updated: 2025/01/20 22:18:42 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./header/minishell.h"


// HOW TO RUN //
// valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=readline.supp -s ./mini

int	process_line(char **line)
{
	printf("%s\n", *line);
	return (0);
}

int	run_minishell(t_data	*data)
{
	char		*line;
	t_tok_line	*token_list;

	token_list = malloc(sizeof(t_tok_line));
	if (!token_list)
		return (1);
	while (true && data->env)
	{
		line = readline("minishell> ");
		if (line)
		{
			create_input_token(line, &token_list);
		//	add_history(line);
		//	clear_history();
			process_line(&line);
			free(line);
		}
		else
			continue ;
		break ; // to remove when more advanced
	}
	free(token_list);
	return (0);
}

int	main(int ac, char **av, char **env)
{
	t_data	data;

	data.env = env;
	if (ac == 1 && env && av)
		run_minishell(&data);
	else
		return (1);
	return (0);
}
