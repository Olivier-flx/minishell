/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   customs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 17:26:38 by ofilloux          #+#    #+#             */
/*   Updated: 2025/04/28 19:31:29 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUSTOMS_H
# define CUSTOMS_H

///// NOT FORGET TO REMOVE FFLUSH() in list_to_msg

//////// Tipos de commentarios ///////
/*
	// @TODO	--> queda por hacer
	// @Util	--> Todavia no se se si va a ser util pero se imagino que si, comprobar en el futuro
	// @debug	--> lineas de codigo hechas para debugear, quitar antes de entregar el proyecto
	// @info	--> informaciones adicionales sobre la logica o un bloc de codigo
	// @confirm	--> need to confirm if it's the best way to do it
	// @optimize --> Codigo que se puede optimisar
	// @NF		--> New Feater : used temporarly while modifying a function
	// @legacy	--> not used anymore, to delete later, kept for logic implementation trace
*/
///////


typedef enum {
	SUCCESS,
	ERROR
} fonction_return_type;

typedef enum {
	CMD,
	PIPE,
	OPERATOR,
	ARG,
	VAR
} string_type;

typedef struct s_quote
{
	int		dbl_quote;
	int		sgl_quote;
	int		acc;
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

typedef struct s_variable
{
	char	*nombre_de_variable;
	char	*valor;
}	t_var;

typedef struct	s_env
{
	char	*key;
	char	*value;
	struct	s_env *next;
}	t_env;

typedef struct data //aqui iremos agregando todo lo que este alocado.A partir de esta poder acceder a toda la info.
{
	char		**env;
	t_env		*env_list;
	t_dlist		*cmd_list;
	t_int_array	ope_char_i; // @util ?//index of operators characters in string input
	t_int_array	token_separators_char_i; //index of separators characters in string input
	int			chunks; //number of commands and argv separated by operators
	t_dlist		*local_var; // @Util ?
}	t_data;

typedef struct s_chunk
{
	char		**tokens; // basic chunks that are taken from line splited by "|"
	char		**argv;
	string_type	type;
	bool		has_redir;
	int			redir_count;
	////// REDIR FILES //////
	char		**redir;// list of redir in a chunk ex: > >> >
	int			redir_file_count;
	char		**redir_files;// ex:test ; test1; test2
	int			*file_fd;
	bool		file_fd_malloced;
	bool		*file_open;
	bool		file_open_malloced;
	////
	char		**input_redir;
	char		**input_redir_file;
	int			index; // util ?
	int			len; // util ?
	t_quote		quotes; // util ?
}	t_chunk;

typedef struct s_local_var
{
	char	*content;
	char	*var_name;
} t_loc_var;


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

///// core functions
int	create_input_token_v3(char *line,  t_dlist **cmd_list, t_data *data);


/////////////// SRC //////////////
	///////// EXEC/////////
int	main_exec(t_data *data);
int	init_files(t_data *data);


	///// Tokens /////
t_chunk	*create_token(char ***str, int type, int i, t_quote quotes);
void	set_separator_char_i_struc_arr(char *src, t_int_array *arr);
int		is_seperator(char *src, int i, t_quote *quote);
int		count_files_in_chunks(char **content);

		// operators.c
int		is_operator(char *src, int i, t_quote *quote);
int		is_redirection(char *src, int i, t_quote *quote);
int		count_operador_from_pp_char(char **content);
int		count_operador(char *src);
int		get_operador_index(char *src, t_dlist **cmd_list);
void	init_operador_var(t_quote *quote, int *op_count, int *i);

		// verifications //
			//user_input_validation
int	check_for_user_input_error(t_dlist **cmd_list);
int	check_for_triple(t_dlist **cmd_list);
int	check_for_simple(t_dlist **cmd_list);
int	line_accolade_closed(char *line);

			//system_input_validation
void	check_system_input_error(t_data *data, t_dlist **cmd_list);
		//cleaning.c

void	set_ope_char_i_struc_arr(char *src, t_int_array *arr);
void	set_ope_char_i_arr(char *src, t_int_array *arr);


int		create_input_to_commands(char *src, t_dlist **cmd_list, t_data *data);

/////////////// UTILS ///////////////
	/////  string //////
void	quote_increment(char *src, int i, t_quote *quote);
char	**split_quoted(char const *s, char c);// @legacy
char	**split_quoted2(char *s,t_data *data);
char	**dup_pp_char(char **substring_arr, int start, int end);

char	*ft_trim(char *src, bool is_malloced);
	//quotes
void	init_quotes(t_quote *quote);
bool	tocken_quote_closed(char *s);
bool	quote_are_closed(t_quote *quote);

// basics
int		s_len(const char *s);
char	*s_dup(char *s);

// custom basics
char	*c_strjoin(char *s1, char *s2, char c);
char	*c_ft_substr(char const *s, unsigned int start, size_t len);

// List Utils
void	free_list(t_dlist *stack_to_free);
void	free_list1(t_dlist **stack_to_free);
int		add_to_list(t_dlist **line, void *content);
void	print_dlist(t_dlist **list);
t_dlist	*find_last_node(t_dlist **lst);

// arrays
bool	int_var_in_arr(int var, t_int_array *arr);
int		pp_char_len(char **array);
void	print_int_arr(t_int_array *arr);
void	print_pp_char_arr(char **str);
// arrays_free
void	free_av(char **av);
char	**free_uncomplete_av(char **av, int i);

// ERROR
	//MSG
void	simple_error_msg(char *msg);
void debug_print_cmd_list(t_dlist **cmd_list_ptr); //@debug

// FREES
void	free_cmdlist(t_dlist *cmd_list);



//Temporal for pruebas
int	create_main_chunks(char *src, t_dlist **cmd_list, t_data *data);

#endif
