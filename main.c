/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 17:36:45 by marvin            #+#    #+#             */
/*   Updated: 2025/04/23 17:36:45 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

// Prototipos de funciones
void print_environment(t_env *env);  // Cambiado para recibir t_env*
void test_builtins(t_env *env);      // Añadido parámetro t_env*

int main(int argc, char **argv, char **environ)
{
    (void)argc;  // Corregido de 'ac' a 'argc'
    (void)argv;   // Corregido de 'av' a 'argv'

    t_env *env = ft_init_env(environ);  // Inicializa el entorno

    printf("\n=== Variables de Entorno ===\n");
    print_environment(env);             // Pasa la lista enlazada

    printf("\n=== Probando Built-ins ===\n");
    test_builtins(env);                 // Pasa 'env' a las pruebas

    ft_free_env(env);                   // Libera memoria al final
    return (0);
}

void print_environment(t_env *env)      // Ahora recibe t_env*
{
    while (env != NULL)
    {
        printf("%s=%s\n", env->key, env->value);  // Imprime clave=valor
        env = env->next;
    }
}

void test_builtins(t_env *env)          // Recibe t_env* como parámetro
{
    // Probando pwd
    printf("\n1. Probando 'pwd':\n");
    ft_pwd();

    // Probando echo
    printf("\n2. Probando 'echo hello world':\n");
    char *echo_args[] = {"echo", "hello", "world", NULL};
    ft_echo(env, echo_args);

    // Probando echo sin argumentos
    printf("\n3. Probando 'echo' sin argumentos:\n");
    char *echo_no_args[] = {"echo", NULL};
    ft_echo(env, echo_no_args);

    // Probando echo con opción -n
    printf("\n4. Probando 'echo -n hello world':\n");
    char *echo_n_args[] = {"echo", "-n", "hello", "world", NULL};
    ft_echo(env, echo_n_args);
}