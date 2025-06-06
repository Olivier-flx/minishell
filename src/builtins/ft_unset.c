/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 11:32:50 by marvin            #+#    #+#             */
/*   Updated: 2025/06/06 22:29:30 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	ft_unset(t_env **env, char **args)
{
	int	i;
	int	ret_status;

	i = 1;
	ret_status = 0;
	if (!args[1])
		return (0);

	while (args[i])
	{
		if (!is_valid_env_key(args[i]))
		{
			ft_putstr_fd("minishell: unset: `", 2);
			ft_putstr_fd(args[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			ret_status = 1;
		}
		else
			ft_unsetenv(env, args[i]);
		i++;
	}
	return (ret_status);
}

// ----------------------------
// MAIN de prueba (¡eliminar después de probar!)
// ----------------------------
/*#ifdef TEST_UNSET

int	main(int argc, char **argv)
{
	(void)argc;

	t_env *env = NULL;

	ft_env_add_back(&env, ft_new_env_node("VAR1", "valor1"));
	ft_env_add_back(&env, ft_new_env_node("VAR2", "valor2"));
	ft_env_add_back(&env, ft_new_env_node("VAR3", "valor3"));

	printf("=== ANTES ===\n");
	for (t_env *tmp = env; tmp; tmp = tmp->next)
		printf("%s=%s\n", tmp->key, tmp->value);

	printf("\n=== Ejecutando unset...\n");
	ft_unset(argv, &env);

	printf("\n=== DESPUÉS ===\n");
	for (t_env *tmp = env; tmp; tmp = tmp->next)
		printf("%s=%s\n", tmp->key, tmp->value);

	ft_free_env(env);
	return (0);
}

int main(int argc, char **argv)
{
    (void)argc;

    // 1. Imprime los argumentos recibidos
    printf("=== Argumentos recibidos ===\n");
    for (int i = 0; argv[i]; i++)
        printf("argv[%d] = %s\n", i, argv[i]);

    // 2. Crea manualmente las variables si no existen
    t_env *env = ft_init_env();
    printf("\n=== Lista REAL en memoria ===\n");
    t_env *tmp = env;
    while (tmp)
    {
         printf("%p: %s=%s\n", (void *)tmp, tmp->key, tmp->value);
        tmp = tmp->next;
    }
    ft_setenv(&env, "VAR1", "valor1"); // Fuerza la creación
    ft_setenv(&env, "VAR2", "valor2");

    // 3. Debug: muestra el entorno ANTES de unset
    printf("\n=== Entorno ANTES de unset ===\n");
   // t_env *tmp = env;
    while (tmp) {
        printf("%s=%s\n", tmp->key, tmp->value);
        tmp = tmp->next;
    }

    // 4. Ejecuta unset
    printf("\n=== Ejecutando unset ===\n");
    int status = ft_unset(argv, &env);

    // 5. Debug: muestra el entorno DESPUÉS de unset
    printf("\n=== Entorno DESPUÉS de unset ===\n");
    tmp = env;
    while (tmp) {
        printf("%s=%s\n", tmp->key, tmp->value);
        tmp = tmp->next;
    }

    ft_free_env(env);
    return status;
}

#endif*/
