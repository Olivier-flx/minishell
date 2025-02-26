/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   system_input_validation.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 15:19:05 by ofilloux          #+#    #+#             */
/*   Updated: 2025/02/26 16:57:17 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	check_system_input_error(t_data *data, t_dlist **cmd_list)
{
 // >	Redirección a un archivo sin permisos	bash: /root/file.txt: Permission denied
 // >>	Añadir a un archivo sin permisos	bash: /root/file.txt: Permission denied
 // <	Redirección desde un archivo inexistente	bash: non_existent_file.txt: No such file or directory
 // |	Con malos commandos despues
}
