/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 16:23:22 by ofilloux          #+#    #+#             */
/*   Updated: 2025/04/27 09:04:53 by ofilloux         ###   ########.fr       */
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


	cmd_list = NULL;
	data->cmd_list = cmd_list;
	return (0);
}


int	run_minishell(t_data	*data)
{
	char		*line;
	int			control;

	control = 0;
	while (true && data->env)
	{
		line = NULL;
		initialize_cmd_list(data);
		line = readline("minishell> ");
		while (line && !tocken_quote_closed(line))
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

		if (line && tocken_quote_closed(line))
		{
			//////////// Anadir Validation del input /////////
			// fonction de validacion de input
			/////////////////////////////
			control = create_input_token_v3(line, &data->cmd_list, data);
			if (control == 3)
			{
				free_cmdlist(data->cmd_list);
				if (data->token_separators_char_i.size > 0)
					free (data->token_separators_char_i.array);
				free(line);
				continue;
			}
			main_exec(data);
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
				free (data->token_separators_char_i.array);
			free(line);
		}
		if (data->cmd_list)
			free_cmdlist(data->cmd_list);
		// else
		// 	continue ;
		ft_free_env(data->env_list);// @debug
		break ; // @debug : to remove when more advanced
	}
	// ft_free_env(data->env_list);// @debug
	return (0);
}

int	main(int ac, char **av, char **env)
{
	t_data	data;

	if (!env)
		return(printf("No environment defined\n"), 1);
	data.env = env;
	data.env_list = ft_init_env(env);
	data.cmd_list = NULL;
	data.ope_char_i = (t_int_array) {0}; // @util ?
	data.token_separators_char_i = (t_int_array) {0};

	if (ac == 1 && env && av) // modificcar para arrancar igual si no hay env
		return(run_minishell(&data));
	else
		return (/* ft_free_env(data.env_list), */ ERROR);
	return (0);
}
