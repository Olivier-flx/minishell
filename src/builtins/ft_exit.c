/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 17:48:14 by marvin            #+#    #+#             */
/*   Updated: 2025/04/28 17:48:14 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int ft_exit(char **args)
{
    int i;
    int exit_code;

    write(STDERR_FILENO, "exit\n", 5);
    if (args[1])
    {
        i = 0;
        // Verifica si el argumento es numérico
        while (args[1][i])
        {
            if (!ft_isdigit(args[1][i]) && !(i == 0 && (args[1][i] == '+' || args[1][i] == '-')))
            {
                write(STDERR_FILENO, "minishell: exit: numeric argument required\n", 43);
                exit(255);
            }
            i++;
        }
        // Verifica si hay demasiados argumentos
        if (args[2])
        {
            write(STDERR_FILENO, "minishell: exit: too many arguments\n", 36);
            return (1);// Devuelve 1 para indicar error sin salir del shell
        }
        exit_code = ft_atoi(args[1]);
        exit(exit_code % 256);
    }
    // Si no hay argumentos, salir con código 0
    exit(0);
}

int main(int argc, char **argv, char **envp) 
{
    (void)argc;
    (void)envp;
    
    return ft_exit(argv);
}