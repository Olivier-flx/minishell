/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 16:23:22 by ofilloux          #+#    #+#             */
/*   Updated: 2025/01/20 18:09:59 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./header/minishell.h"

int	process_line(char **line)
{
	printf("%s\n", *line);
	free (*line);
	return (0);
}

int	run_minishell(t_data	*data)
{
	char		*line;
	t_tok_line	*token_list;

	while (true && data->env)
	{
		line = readline("minishell> ");
		if (line)
		{
			create_input_token(line, &token_list);
		//	add_history(line);
			process_line(&line);
			free(line);
		}
		else
			continue ;
		break ; // to remove when more advanced
	}
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
