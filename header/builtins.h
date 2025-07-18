/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 18:13:34 by laufarin          #+#    #+#             */
/*   Updated: 2025/07/14 20:30:41 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

//# include "minishell.h"  // Para reutilizar structs y funciones comunes
//# include "customs.h"

typedef struct s_data	t_data;

typedef struct s_env
{
	char			*key;
	char			*value;
	bool			is_exported; //1 = in ENV, if 0 --> global variable
	struct s_env	*next;
}	t_env;

// Prototipos de built-ins
int		ft_echo(t_env *env, char **args);
int		ft_cd(t_env **env, char **args);
int		ft_pwd(void);
int		ft_export(t_env **env, char **args);
int		ft_unset(t_env **env, char **args);
int		ft_env(t_env *env);
int		ft_exit(t_data *data, char **args);
int		ft_exit_child(t_data *data, char **args);

// int  update_pwds(t_env **env);

//enviroment
t_env	*ft_new_env_node(char *key, char *value, bool exported);
void	ft_env_add_back(t_env **head, t_env *new_node);
t_env	*ft_init_env(char **env);
char	*ft_getenv(t_env *env, char *key);
int		ft_env_exists(t_env *env, char *key);
void	is_minishell(t_data *data, char *arg_0);

//env_utils
void	ft_free_env(t_env *env);
void	ft_setenv(t_env **env, char *key, char *value);
void	ft_unsetenv(t_env **env, char *key);
int		ft_env_size(t_env *env);
char	**ft_env_to_array(t_env *env);

int		is_valid_env_key(char *key);
void	update_or_add_env(t_env **env, char *key, char *value);
int		print_sorted_env(t_env *env);
char	**env_to_sorted_array(t_env *env);

void	ft_print_env(t_env *env);

char	*ft_strjoin3(char *s1, char *s2, char *s3);
#endif
