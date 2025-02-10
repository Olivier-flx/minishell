/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   customs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 17:26:38 by ofilloux          #+#    #+#             */
/*   Updated: 2025/02/10 22:09:18 by ofilloux         ###   ########.fr       */
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

typedef struct s_quote
{
	int		sgl;
	int		dbl;
}	t_quote;

typedef struct {
	int	*array;
	int	size;
} t_int_array;

typedef struct data
{
	char		**env;
	t_list		*input;
	t_int_array	operator_char_i; //index of operators characters in string input
	int			chunks; //number of commands and argv separated by operators
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
	int			index;
	int			len;
	t_quote		quotes;
}	t_input_tocken;




//NOT USED
typedef struct s_operator
{
	char	*tocken;
	int		index;
	int		len;
}	t_operator;



// buildins
int		echo(char string);
int		env(char **env);
int		b_exit(int ret_val, t_data data);
//int		create_input_token(char *src, t_list **line);



/////////////// SRC //////////////
	///// Tokens /////
		// operators.c
int		is_operator(char *src, int i);
int		count_operador(char *src);
int		get_operador_index(char *src, t_list **cmd_list);
void	init_operador_var(t_quote *quote, int *op_count, int *i);


void set_operator_char_i_size(char *src, t_int_array *arr);
void set_operator_char_i_arr(char *src, t_int_array *arr);


int		create_input_to_commands(char *src, t_list **cmd_list, t_data *data);

/////////////// UTILS ///////////////
	/////  string //////
void	increment_quotes(char *src, int i, t_quote *quote);

// basics
int		s_len(const char *s);
char	*s_dup(char *s);


// List Utils
void	free_list(t_list **stack_to_free);
int		add_to_list(t_list **line, void *content);
void	print_list(t_list **list);

// arrays
bool	int_var_in_arr(int var, t_int_array arr);


// ERROR
	//MSG
void	simple_error_msg(char *msg);

#endif
