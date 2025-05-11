/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 16:23:22 by ofilloux          #+#    #+#             */
/*   Updated: 2025/05/11 20:08:44 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./header/minishell.h"

// HOW TO RUN //
// valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=readline.supp -s ./mini

volatile sig_atomic_t g_signal_received = 0;

int initialize_cmd_list(t_data *data)
{
	t_dlist		*cmd_list;

	cmd_list = NULL;
	data->cmd_list = cmd_list;
	return (0);
}

int	run_minishell(t_data	*data)
{
	int			control;

	control = 0;
	while (true && data->env)
	{
		initialize_cmd_list(data);
		data->line = readline("\033[1;32mminishell> \033[0m");
		if (!data->line)  // Caso Ctrl+D
			handle_ctrl_d(data);
		if (g_signal_received)
		{
			data->exit_status = g_signal_received;
			g_signal_received = 0;
		}

		while (data->line && !tocken_quote_closed(data->line))
			data->line = c_strjoin(data->line, readline("\033[1mdquote> \033[0m"), '\n');
		while (data->line && !line_accolade_closed(data->line))
			data->line = c_strjoin(data->line, readline("> "), '\n');
		if (data->line && tocken_quote_closed(data->line))
		{
			control = create_chunks(data->line, &data->cmd_list, data);
			if (control != 3 )
				main_exec(data);
			add_history(data->line);
		}
		free_resources(data, false, true);
		g_signal_received = 0;
	}
	rl_clear_history();
	return (0);
}

void initialize_data(t_data *data, char **env)
{
	data->env = env;
	data->env_list = ft_init_env(env);
	data->line = NULL;
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

	if (ac == 1 && av) // modificcar para arrancar igual si no hay env
	{
		setup_signals();
		return (run_minishell(&data));
	}
	else
		return (ft_free_env(data.env_list),  EXIT_FAILURE);
	return (0);
}


/////////////////// LAURA //////////////////////


/* void free_resources(t_data *data)
{
    if (data->env_list)
        ft_free_env(data->env_list);
    if (data->cmd_list)
        free_cmdlist(data->cmd_list);
    // Liberar cualquier otro recurso si es necesario
}

int main(int ac, char **av, char **env)
{
    t_data data;

    if (!env)
        return (printf("No environment defined\n"), 1);

    // Inicialización de la estructura data
    ft_memset(&data, 0, sizeof(t_data));
    data.env_list = ft_init_env(env);
    data.exit_status = 0;

    if (ac == 1)  // Modo interactivo

        run_minishell(&data);

    free_resources(&data);
    return (data.exit_status);
}
 */
