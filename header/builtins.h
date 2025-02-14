/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laufarin <laufarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 18:13:34 by laufarin          #+#    #+#             */
/*   Updated: 2025/02/14 18:15:28 by laufarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"  // Para reutilizar structs y funciones comunes


typedef struct	s_env
{
    char	*key;
    char	*value;
    struct	s_env *next;
}	t_env;
	

// Prototipos de built-ins
int	ft_echo(char **args);
int	ft_cd(char **args);
int	ft_pwd(void);
int	ft_export(char **args);
int	ft_unset(char **args);
int	ft_env(char **args);
int	ft_exit(char **args);

#endif

