/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 11:53:38 by marvin            #+#    #+#             */
/*   Updated: 2025/04/22 11:53:38 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int ft_export(t_env **env, char **args)
{
    int i = 1;
    int status = 0;

    if (!args[i])
        return (print_sorted_env(*env));

    while (args[i])
    {
        char *equal_sign = ft_strchr(args[i], '=');
        char *key = args[i];

        if (equal_sign)
            *equal_sign = '\0';

        if (!is_valid_env_key(key))
        {
            write(STDERR_FILENO, "minishell: export: `", 20);
            write(STDERR_FILENO, args[i], ft_strlen(args[i]));
            write(STDERR_FILENO, "`: not a valid identifier\n", 25);
            status = 1;
        }
        else if (equal_sign)
        {
            *equal_sign = '=';
            update_or_add_env(env, key, equal_sign + 1);
        }
        i++;
    }
    return status;
}