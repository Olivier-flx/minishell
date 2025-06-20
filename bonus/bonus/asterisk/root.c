/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   root.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 19:08:36 by ofilloux          #+#    #+#             */
/*   Updated: 2025/06/16 19:12:58 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

/**
 *  @brief The root of the asterisk extention
 *         used in retocken_after_expension()
 *
 *  @param	str char *string
 */
void	expend_asterisk(char *str)
{
	printf("desde expend_asterisk `%s`\n", str);
}
