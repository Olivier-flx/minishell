/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviro.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 18:33:21 by marvin            #+#    #+#             */
/*   Updated: 2025/05/11 18:07:27 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../header/minishell.h"

t_env *ft_new_env_node(char *key, char *value, bool exported)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if(!node)
		return(NULL);

	node->key = ft_strdup(key);
	node->value = ft_strdup(value);
	node->is_exported = exported;
	node->next = NULL;
	return(node);
}

void ft_env_add_back(t_env **head, t_env *new_node)
{
	t_env	*last;

	if(!*head)
	{
		*head = new_node;
		return;
	}
	last = *head;
	while(last->next)
	{
		last = last->next;
	}
	last->next = new_node;
}

static void init_eq_key_val(char **eq,char **key, char **val)
{
	*eq = NULL;
	*key = NULL;
	*val = NULL;
}

//#include <unistd.h> // Para 'environ'

t_env *ft_init_env(char **env)
{
	int	i;
	t_env *head;
	char *equal;
	char *key;
	char *value;

	head = NULL;
	init_eq_key_val(&equal, &key, &value);
	i = -1;
	while (env[++i])
	{
		init_eq_key_val(&equal, &key, &value);
		equal = ft_strchr(env[i], '=');
		key = ft_substr(env[i], 0, equal - env[i]);
		value = ft_strdup(equal + 1);
		ft_env_add_back(&head, ft_new_env_node(key, value, true));
		free(key);  // Liberamos key temporal (ft_substr usa malloc)
		free(value);
	}
	return (head);
}

void ft_print_env(t_env *env)
{
	while (env)
	{
		printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
}
