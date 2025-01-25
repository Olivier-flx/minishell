/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   customs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 17:26:38 by ofilloux          #+#    #+#             */
/*   Updated: 2025/01/25 12:09:21 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef CUSTOMS
# define CUSTOMS
#endif

typedef struct s_token_line t_tok_line;

typedef struct data
{
	char		**env;
	t_tok_line	*input;
} t_data;

typedef struct s_token_line
{
	void				*content;
	struct token_line	*prev;
	struct token_line	*next;
} t_tok_line;

// buildins
int	echo(char string);
int	env(char **env);
int b_exit(int ret_val, t_data data);
int	create_input_token (char *src, t_tok_line **line);
