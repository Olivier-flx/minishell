/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   customs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 17:26:38 by ofilloux          #+#    #+#             */
/*   Updated: 2025/02/19 16:05:37 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef CUSTOMS_H
# define CUSTOMS_H



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

typedef struct s_int_array
{
	int	*array;
	int	size;
}	t_int_array;

typedef struct s_dlist
{
	void			*content;
	struct s_dlist	*prev;
	struct s_dlist	*next;
}	t_dlist;

typedef struct data
{
	char		**env;
	t_dlist		*input;
	t_int_array	ope_char_i; //index of operators characters in string input
	int			chunks; //number of commands and argv separated by operators
}	t_data;

typedef struct s_input_tocken
{
	char		**content;
	string_type	type;
	int			index; // util ?
	int			len; // util ?
	t_quote		quotes; // util ?
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
//int		create_input_token(char *src, t_dlist **line);



/////////////// SRC //////////////
	///// Tokens /////
		// operators.c
int		is_operator(char *src, int i, t_quote *quote);
int		count_operador(char *src);
int		get_operador_index(char *src, t_dlist **cmd_list);
void	init_operador_var(t_quote *quote, int *op_count, int *i);

		//cleaning.c

void	set_ope_char_i_struc_arr(char *src, t_int_array *arr);
void	set_ope_char_i_arr(char *src, t_int_array *arr);


int		create_input_to_commands(char *src, t_dlist **cmd_list, t_data *data);

/////////////// UTILS ///////////////
	/////  string //////
void	increment_quotes(char *src, int i, t_quote *quote);
char	**split_quoted(char const *s, char c);

char	*ft_trim(char *src, bool is_malloced);
	//quotes
void	init_quotes(t_quote *quote);
bool	all_quote_closed(char *s);

// basics
int		s_len(const char *s);
char	*s_dup(char *s);


// List Utils
void	free_list(t_dlist **stack_to_free);
int		add_to_list(t_dlist **line, void *content);
void	print_dlist(t_dlist **list);

// arrays
bool	int_var_in_arr(int var, t_int_array *arr);


// ERROR
	//MSG
void	simple_error_msg(char *msg);

#endif
