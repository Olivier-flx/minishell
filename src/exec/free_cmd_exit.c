/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cmd_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 19:00:27 by ofilloux          #+#    #+#             */
/*   Updated: 2025/05/07 19:00:41 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	clean_exit(t_file *files, t_cmd *cmd, int failure, char *msg)
{
	int	i;

	i = -1;
	while (++i < 2)
	{
		if (files[i].name)
			free(files[i].name);
		if (files[i].content)
			free(files[i].content);
		if (files[i].fd > 0 && files[i].file_open)
			if (close(files[i].fd) == -1)
				perror("Error at closing file while cleaning files : ");
	}
	if (failure == 0 && cmd && cmd->cmd_err_msg == NULL)
		exit(EXIT_SUCCESS);
	if (failure == 0)
		exit(EXIT_SUCCESS);
	write(STDERR_FILENO, msg, ft_strlen(msg));
	if (cmd && cmd->cmd_err_msg)
		free(msg);
	exit(failure);
}

void free_pipes_arr(int **pipe_arr, t_cmd *cmd)
{
	int i;

	i = 0;
	while (i < cmd->cmd_count - 1 && cmd->pipes_malloced[i])
	{
		free(pipe_arr[i]);
		i++;
	}
	free(pipe_arr);
	pipe_arr = NULL;

}

void	clean_cmds_exit(t_cmd *cmd, int exit_val, char *msg)
{
	int i;

	i = 0;
	if (cmd)
	{
		if (cmd->env_path != NULL && cmd->env_path[0] != '\0')
			free(cmd->env_path);
		while (i < cmd->cmd_count && cmd->cmd_vect && cmd->cmd_vect[i])
		{
			free_char_arr(cmd->cmd_vect[i]);
			i++;
		}
		free(cmd->cmd_vect);
		free(cmd->cmd_is_valid_arr);
		if (cmd->pid_arr_malloced == true)
			free(cmd->pid_arr);
		if (cmd->pipe_arr_malloced == true)
			free_pipes_arr(cmd->pipe_arr, cmd);
		if (cmd->pipes_malloced)
			free(cmd->pipes_malloced);
	}
	clean_exit(cmd->files_arr, cmd, exit_val, msg);
}
