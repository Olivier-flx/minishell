/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 11:53:38 by marvin            #+#    #+#             */
/*   Updated: 2025/05/12 17:53:06 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int ft_export(t_env **env, char **args)
{
	int i;
	int status;

	i = 1;
	status = 0;
	if (!env || !args)
		return 1;


	// Caso sin argumentos (mostrar entorno)
	if (!args[i])
		return (print_sorted_env(*env));

	while (args[i])
	{
		if (!args[i]) {
			i++;
			continue;
		}

		char *key_value = ft_strdup(args[i]); // Copiamos el argumento
		if (!key_value) return 1;

		char *equal_sign = ft_strchr(key_value, '=');
		char *key = key_value;
		char *value = NULL;

		if (equal_sign) {
			*equal_sign = '\0'; // Separamos key y value
			value = equal_sign + 1;
		}

		if (!is_valid_env_key(key)) {
			ft_putstr_fd("minishell: export: `", STDERR_FILENO);
			ft_putstr_fd(args[i], STDERR_FILENO);
			ft_putstr_fd("`: not a valid identifier\n", STDERR_FILENO);
			status = 1;
		}
		else if (equal_sign) {
			update_or_add_env(env, key, value);
		}

		free(key_value); // Liberamos la copia
		i++;
	}
	return status;
}
