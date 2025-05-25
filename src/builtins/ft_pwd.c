/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laufarin <laufarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 15:40:44 by laufarin          #+#    #+#             */
/*   Updated: 2025/03/27 17:52:23 by laufarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

/*#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>*/

int ft_pwd(void)
{
    char *cwd;

    cwd = getcwd(NULL, 0); // Asignación dinámica
    if (cwd == NULL)
    {
        ft_putstr_fd("minishell: pwd: ", STDERR_FILENO);
        ft_putstr_fd(strerror(errno), STDERR_FILENO);
        ft_putstr_fd("\n", STDERR_FILENO);
        return (1);
    }
    
    ft_putstr_fd(cwd, STDOUT_FILENO);
    ft_putstr_fd("\n", STDOUT_FILENO);
    free(cwd);
    return (0);
}

/*int main(void)
{
    return (ft_pwd());
}*/
