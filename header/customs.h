/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   customs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 17:26:38 by ofilloux          #+#    #+#             */
/*   Updated: 2025/02/10 20:10:27 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef CUSTOMS_H
# define CUSTOMS_H


typedef struct s_list	t_list;

typedef enum {
    CMD,
    OPERATOR,
    ARG,
    VAR
} string_type;


typedef struct data
{
	char		**env;
	t_list		*input;
}	t_data;

typedef struct s_list
{
	void			*content;
	struct s_list	*prev;
	struct s_list	*next;
}	t_list;

typedef struct s_input_tocken
{
	char		*content;
	string_type	type;
	bool		is_single_quoted;
	bool		is_double_quoted;
	bool		quote_closed;
	bool		is_var;
}	t_input_tocken;

typedef struct s_operator
{
	int		index;
	int		len;
	char	*operator;
}	t_operator;

typedef struct s_quote
{
	int		slg;
	int		dbl;
}	t_quote;

// buildins
int		echo(char string);
int		env(char **env);
int		b_exit(int ret_val, t_data data);
//int		create_input_token(char *src, t_list **line);



/////////////// SRC //////////////
	///// Tokens /////
		// operators.c
int		is_operator(char *src, int i)
int		count_operador(char *src)
int		get_operador_index(char *src, t_list **cmd_list)

int		create_input_to_commands(char *src, t_list **cmd_list);

/////////////// UTILS ///////////////
	/////  string //////

// basics
int		s_len(const char *s);
char	*s_dup(char *s);


// List Utils
void	free_list(t_list **stack_to_free);
int		add_to_list(t_list **line, void *content);
void	print_list(t_list **list);


// ERROR
	//MSG
void	simple_error_msg(char *msg);

#endif
