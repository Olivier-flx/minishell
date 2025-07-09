/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 16:23:22 by ofilloux          #+#    #+#             */
/*   Updated: 2025/07/09 16:28:58 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./header/minishell.h"

// HOW TO RUN //
/* valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes
	--track-origins=yes --suppressions=readline.supp -s ./minishell
*/

volatile sig_atomic_t	g_signal_received = 0;

int	initialize_cmd_list(t_data *data)
{
	t_dlist		*cmd_list;

	cmd_list = NULL;
	data->cmd_list = cmd_list;
	return (0);
}


static void	get_prompt(t_data *data, char **prompt)
{
	char	path[PATH_MAX];
	char	*f_path;
	char	*pwd;

	pwd = NULL;
	f_path = NULL;
	ft_memset(path, 0, PATH_MAX * sizeof(char));
	if (getcwd(path, PATH_MAX) == NULL)
	{
		pwd = ft_getenv(data->env_list, "PWD");
		if (!pwd)
			pwd = ft_getenv(data->env_list, "OLDPWD");
		if (pwd)
			f_path = pwd + ft_strlen(ft_getenv(data->env_list, "HOME"));
	}
	else
		f_path = path + ft_strlen(ft_getenv(data->env_list, "HOME"));
	if (*f_path != '\0')
		*prompt = ft_strjoin3("\001\033[1;32m\002minishell ~", \
			f_path, "> \001\033[0m\002");
	else
		*prompt = ft_strdup("\001\033[1;32m\002minishell ~> \001\033[0m\002");
}

/**
 * @note readline gnu full documentation
 * https://tiswww.case.edu/php/chet/readline/readline.html
 * \001 : start of a non-visible character sequence (SOH, ASCII 1)
 * \002 : end of a non-visible character sequence (STX, ASCII 2)
 */
int	run_minishell(t_data *data)
{
	int			control;
	char		*prompt;

	control = 0;
	while (true && data->env)
	{
		initialize_cmd_list(data);
		get_prompt(data, &prompt);
		data->line = readline(prompt);
		ft_free((void **) &prompt);
		signal_handlers_for_readline(data);
		listen_incomplete_lines(data, &data->line);
		if (data->line && *data->line)
		{
			add_history(data->line);
			control = create_chunks(data->line, &data->cmd_list, data);
			if (control == 0)
				main_exec(data);
		}
		free_resources(data, false, true);
		g_signal_received = 0;
	}
	rl_clear_history();
	return (0);
}

void	initialize_data(t_data *data, char **env)
{
	data->env = env;
	data->env_list = ft_init_env(env);
	data->line = NULL;
	data->cmd_list = NULL;
	data->ope_char_i = (t_int_array){0};
	data->tok_sep_char_i.array = NULL;
	data->tok_sep_char_i.size = 0;
	data->nb_chunks = 0;
	data->exit_status = 0;
	data->exe_nfo.last_status_code = 0;
	data->exe_nfo.cmd_err_msg = NULL;
	data->exe_nfo.env_path = NULL;
	data->exe_nfo.env_path_found = false;
	data->exe_nfo.cmd_is_valid_arr = NULL;
	data->exit_required = false;
	data->exit_code = 0;
}

int	main(int ac, char **av, char **env)
{
	t_data	data;

	data = (t_data){0};
	if (ac > 1)
		return (1);
	if (!env)
		return (printf("No environment defined\n"), 1);
	initialize_data(&data, env);
	if (ac == 1 && av)
	{
		setup_signals();
		return (run_minishell(&data));
	}
	else
		return (ft_free_env(data.env_list), EXIT_FAILURE);
	return (0);
}
