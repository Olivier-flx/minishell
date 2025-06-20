/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub_proc_sig.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 22:17:16 by ofilloux          #+#    #+#             */
/*   Updated: 2025/06/18 19:15:13 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

/**
 * @brief handle_sub_process_signal - Process the termination status of
 *                a child process and update the shell's exit state accordingly.
 *
 * @param data   : pointer to data
 * @param status :  The status value returned by wait() or waitpid(),
 *                  how the child process terminated.
 * @param printed:  Pointer to a boolean flag used to ensure that the message
 *            "Quit (core dumped)" is printed only once.
 *
 * @brief This function interprets the exit status of a child process.
 * It handles both normal termination and signal-induced termination:
 *
 * - If the child terminated due to a signal (e.g., SIGINT or SIGQUIT):
 *   - If the signal was SIGQUIT and the message hasn't already been printed,
 *     it writes "Quit (core dumped)" to stdout and sets the `printed` flag.
 *   - It sets `data->exit_status` to 128 plus the signal number, which follows
 *     the standard Unix convention for encoding signal-based termination.
 *
 * - If the child didn't exited normally, it extracts the actual exit code
 *   from the status using `status & 0xFF` : mimics WIFSIGNALED(STATUS).
 * - If the child exited normally it mimics __WEXITSTATUS
 *  @see man wait. for WEXITSTATUS and WIFSIGNALED AND wait.h
 *  @see /usr/include/x86_64-linux-gnu/bits/waitstatus.h
 *
 * This function helps the shell reflect the child's termination reason.
 */
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
