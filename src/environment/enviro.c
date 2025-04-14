/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 18:33:21 by marvin            #+#    #+#             */
/*   Updated: 2025/04/10 18:33:21 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "builtins.h"

t_env *ft_new_env_node(char *key, char *value)
{
    t_env   *node = malloc(sizeof(t_env));
    if(!node)
    return(NULL);

    node->key = ft_strdup(key);
    node->value = ft_strdup(value);
    node->next = NULL;
    return(node);
}

void ft_env_add_back(t_env **head, t_env *new_node)
{
    t_env   *last;
    if(!*head)
    {
       *head =  new_node;
       return;
    }
    last = *head;
    while(last->next)
    {
        last = last->next;
    }
    last->next = new_node;
}

t_env *ft_init_env(char **env)
{
    t_env *head = NULL;
    int i = 0;
    
    while (env[i])
    {
        char *equal = ft_strchr(env[i], '=');
        char *key = ft_substr(env[i], 0, equal - env[i]);
        char *value = ft_strdup(equal + 1);
        
        ft_env_add_back(&head, ft_new_env_node(key, value));
        free(key);  // Liberamos key temporal (ft_substr usa malloc)
        i++;
    }
    return (head);
}