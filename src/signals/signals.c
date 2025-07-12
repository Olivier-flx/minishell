/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 14:28:21 by marvin            #+#    #+#             */
/*   Updated: 2025/07/12 14:48:15 by ofilloux         ###   ########.fr       */
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

/**
 * @brief Signal handler for SIGINT and SIGQUIT signals.
 *
 * - On SIGINT (e.g., Ctrl+C):
 *   - Sets the global variable `g_signal_received` to 130 (custom exit code).
 *   - If Readline is currently reading a command (checked using
 *     `rl_readline_state & RL_STATE_READCMD`), it refreshes the prompt
 *     using `rl_redisplay()` to show the clean line.
 *
 * - On SIGQUIT (e.g., Ctrl+\):
 *   - Only handled if Readline is NOT actively reading a command, i.e.
 *     `!(rl_readline_state & RL_STATE_READCMD)` is true.
 *     Happens when a child process is running, not during prompt input.
 *   - In this case, sets `g_signal_received` to 131 and prints
 *     "Quit (core dumped)" to stdout.
 *
 * @param sig The signal number received (SIGINT or SIGQUIT).
 * @note cat /usr/include/readline/readline.h for RL_STATE_READCMD
 *           and rl_readline_state
 *           rl_readline_state is a global variable set by readline library,
 *           RL_STATE_READCMD is a binary defined in readline library.
 *
 */
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

/**
 * @brief Configure custom signal handlers for the shell session.
 *
 * Sets up signal handling for an interactive shell:
 * - SIGINT (Ctrl+c)
 * - SIGQUIT (Ctrl+\)
 * - SIGTSTP (Ctrl+Z)
 *
 * Set sa.sa_mask to emptyset so no signal are bloqued during handler exec
 *
 * @see handle_signal
 * @see /usr/include/asm-generic/signal-defs.h for SIG_IGN
 */
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

/**
 * @brief Restore signals to defauld in case of being in a child process
 *        and not in a readline anymore.
 *
 *       - sa.sa_handler = SIG_DFL; restore handler to default
 */
void	reset_signals_to_default(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_handler = SIG_DFL;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}

void	handle_ctrl_d(t_data *data)
{
	write(STDOUT_FILENO, "exit\n", 5);
	free_resources(data, true, true);
	exit(data->exit_status);
}
