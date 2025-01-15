/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   customs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 17:26:38 by ofilloux          #+#    #+#             */
/*   Updated: 2025/01/12 20:41:16 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef CUSTOMS
# define CUSTOMS
#endif

typedef struct data
{
	char	**env;
} t_data;


// buildins
int	echo(char string);
int	env(char **env);
int b_exit(int ret_val, t_data data);
