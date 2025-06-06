/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 14:28:21 by marvin            #+#    #+#             */
/*   Updated: 2025/06/06 21:40:44 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"
//#include <signal.h>
// Solo esta global está permitida (fuera de estructuras)
//volatile sig_atomic_t g_signal_received = 0; // @confirm

void	signal_handlers_for_readline(t_data *data)
{
	if (!data->line)
		handle_ctrl_d(data);
	if (g_signal_received)
	{
		data->exit_status = g_signal_received;
		g_signal_received = 0;
	}
}

// cat /usr/include/readline/readline.h for RL_STATE_READCMD
void	handle_signal(int sig)
{
	if (sig == SIGINT)
	{
		g_signal_received = 130;
		write(STDOUT_FILENO, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		if (rl_readline_state & RL_STATE_READCMD)
			rl_redisplay();
	}
	if (sig == SIGQUIT && !(rl_readline_state & RL_STATE_READCMD))
	{
		g_signal_received = 131;
		write(STDOUT_FILENO, "Quit (core dumped)\n", 20);
	}
}

void	setup_signals(void)
{
	struct sigaction	sa;

	sa.sa_handler = handle_signal;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);

	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
	sigaction(SIGTSTP, &sa, NULL);
}
//IT (Ctrl+\) -> ignorar

void	handle_sub_process_signal(t_data *data, int status, bool *printed)
{
	int		sig;

	if (!status)
		return ;
	if ((status & 0x7F) != 0)
	{
		sig = status & 0x7F;
		if (sig == SIGQUIT)
		{
			if (!(*printed))
			{
				write(STDOUT_FILENO, "Quit (core dumped)\n", 20);
				*printed = true;
			}

			data->exit_status = 128 + SIGQUIT;
		}
		else if (sig == SIGINT)
			data->exit_status = 128 + SIGINT;
		else
			data->exit_status = 128 + sig;
	}
	else
		data->exit_status = (status >> 8) & 0xFF;
}

void	reset_signals_to_default(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_handler = SIG_DFL;
	sa.sa_flags = 0;

	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}

void	handle_ctrl_d(t_data *data)
{
	write(STDOUT_FILENO, "exit\n", 5);
	free_resources(data, true, true);
	exit(data->exit_status);
}
