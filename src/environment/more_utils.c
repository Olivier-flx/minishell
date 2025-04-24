/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 17:20:12 by marvin            #+#    #+#             */
/*   Updated: 2025/04/23 17:20:12 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

char **env_to_sorted_array(t_env *env)
{
    int     count = 0;
    t_env   *tmp = env;
    char    **array;
    int     i = 0;

    // 1. Contar el número de variables
    while (tmp && ++count)
        tmp = tmp->next;

    // 2. Reservar memoria para el array (+1 para el NULL final)
    array = (char **)malloc((count + 1) * sizeof(char *));
    if (!array)
        return (NULL);

    // 3. Llenar el array con las variables "key=value"
    tmp = env;
    while (tmp)
    {
        array[i] = ft_strjoin3(tmp->key, "=", tmp->value);
        if (!array[i])
        {
            // Liberar memoria si hay error
            while (--i >= 0)
                free(array[i]);
            free(array);
            return (NULL);
        }
        tmp = tmp->next;
        i++;
    }
    array[count] = NULL;

    // 4. Ordenar alfabéticamente (usando ft_strcmp)
    qsort(array, count, sizeof(char *), 
        (int (*)(const void *, const void *))ft_strcmp);

    return (array);
}


int print_sorted_env(t_env *env)
{
    char **env_array = env_to_sorted_array(env); // Convierte a array y ordena
    int i = 0;

    while (env_array[i])
    {
        printf("declare -x %s\n", env_array[i]); // Formato "declare -x VAR=valor"
        free(env_array[i]); // Libera cada string
        i++;
    }
    free(env_array); // Libera el array
    return (0);
}

void update_or_add_env(t_env **env, char *key, char *value)
{
    t_env *current = *env;

    while (current) // Busca si la variable ya existe
    {
        if (ft_strcmp(current->key, key) == 0)
        {
            free(current->value); // Libera el valor antiguo
            current->value = ft_strdup(value); // Asigna el nuevo valor
            return;
        }
        current = current->next;
    }
    // Si no existe, añade un nuevo nodo al final
    ft_env_add_back(env, ft_new_env_node(ft_strdup(key), ft_strdup(value)));
}

int is_valid_env_key(char *key)
{
    if (!key || !*key || ft_isdigit(*key)) // Si está vacío o empieza con número
        return (0);

    while (*key)
    {
        if (!ft_isalnum(*key) && *key != '_') // Caracteres no permitidos
            return (0);
        key++;
    }
    return (1);
}