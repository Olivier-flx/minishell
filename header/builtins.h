/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laufarin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 15:57:31 by laufarin          #+#    #+#             */
/*   Updated: 2025/02/13 20:02:23 by laufarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"  // Para reutilizar structs y funciones comunes


typedef struct	//estructura para el env
{
	//name
	//value
	//next
}	

// Prototipos de built-ins
int	ft_echo(char **args);
int	ft_cd(char **args);
int	ft_pwd(void);
int	ft_export(char **args);
int	ft_unset(char **args);
int	ft_env(char **args);
int	ft_exit(char **args);

#endif

