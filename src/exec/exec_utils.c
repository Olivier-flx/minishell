/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 16:38:15 by marvin            #+#    #+#             */
/*   Updated: 2025/05/10 16:38:15 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

bool is_builtin(char *cmd)
{
    char *builtins[] = {"echo", "cd", "pwd", "export", 
                       "unset", "env", "exit", NULL};
    int i = 0;
    
    while (builtins[i])
        if (!ft_strcmp(cmd, builtins[i++]))
            return (true);
    return (false);
}