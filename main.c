/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 16:23:22 by ofilloux          #+#    #+#             */
/*   Updated: 2025/05/10 16:25:30 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./header/minishell.h"


// HOW TO RUN //
// valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=readline.supp -s ./minishell

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
		while (line && !line_accolade_closed(line))
			line = c_strjoin(line, readline("> "), '\n');
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
			control = create_chunks(line, &data->cmd_list, data);
			if (control == 3)
			{
				free_cmdlist(data->cmd_list);
				if (data->token_separators_char_i.size > 0)
					ft_free((void **)&data->token_separators_char_i.array);
				ft_free((void **)&line);
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
			if (data->token_separators_char_i.size > 0)
			{
				data->token_separators_char_i.size = 0;
				if (data->token_separators_char_i.array)
					ft_free((void **)&data->token_separators_char_i.array);;
			}
			ft_free((void **)&line);
		}
		if (data->cmd_list)
		{
			free_cmdlist(data->cmd_list);
			clean_cmds_exit(data, EXIT_SUCCESS);
		}
		// else
		// 	continue ;
		//ft_free_env(data->env_list);// @debug
		//break ; // @debug : to remove when more advanced
	}
	// ft_free_env(data->env_list);// @debug
	return (0);
}

void initialize_data(t_data *data, char **env)
{
	data->env = env;
	data->env_list = ft_init_env(env);
	data->cmd_list = NULL;
	data->ope_char_i = (t_int_array) {0}; // @util ?
	//data->token_separators_char_i = (t_int_array) {0};
	data->token_separators_char_i.array = NULL;
	data->token_separators_char_i.size = 0;
	data->nb_chunks = 0;
	data->exec_info.env_path = NULL;
	data->exec_info.env_path_found = false;
	data->exec_info.cmd_is_valid_arr = NULL;
}

int	main(int ac, char **av, char **env)
{
	t_data	data;

	data = (t_data) {0};
	if (ac > 1)
		return (1);
	if (!env)
		return(printf("No environment defined\n"), 1);
	initialize_data(&data, env);


	if (ac == 1 && env && av) // modificcar para arrancar igual si no hay env
		return (run_minishell(&data));
	else
		return (ft_free_env(data.env_list),  EXIT_FAILURE);
	return (0);
}

/*
/////////////////// LAURA //////////////////////
// Prototipos de funciones
void print_environment(t_env *env);  // Cambiado para recibir t_env*
void test_builtins(t_env *env);      // Añadido parámetro t_env*

void print_environment(t_env *env)       Ahora recibe t_env*
	{
		while (env != NULL)
		{
        printf("%s=%s\n", env->key, env->value);  // Imprime clave=valor
        env = env->next;
    }
}

void test_builtins(t_env *env)          // Recibe t_env* como parámetro
{
    // Probando pwd
    printf("\n1. Probando 'pwd':\n");
    ft_pwd();

    // Probando echo
    printf("\n2. Probando 'echo hello world':\n");
    char *echo_args[] = {"echo", "hello", "world", NULL};
    ft_echo(env, echo_args);

    // Probando echo sin argumentos
    printf("\n3. Probando 'echo' sin argumentos:\n");
    char *echo_no_args[] = {"echo", NULL};
    ft_echo(env, echo_no_args);

    // Probando echo con opción -n
    printf("\n4. Probando 'echo -n hello world':\n");
    char *echo_n_args[] = {"echo", "-n", "hello", "world", NULL};
    ft_echo(env, echo_n_args);
}*/
