/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   customs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 17:26:38 by ofilloux          #+#    #+#             */
/*   Updated: 2025/05/08 20:11:25 by ofilloux         ###   ########.fr       */
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
	VAR
} chunk_type;

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

typedef struct	s_env
{
	char	*key;
	char	*value;
	bool	is_exported; //1 = in ENV, if 0 --> global variable
	struct	s_env *next;
}	t_env;

// struc to store the good path for commands.
typedef struct s_exec_data
{
	char	*env_path;
	bool	env_path_found;
	bool	*cmd_is_valid_arr; // check ether each argv in each chunk is valid or not
	bool	cmd_is_valid_arr_malloced;
	int		*pid_arr; // USED ??
	bool	pid_arr_malloced;
	int		**pipe_arr;
	bool	pipe_arr_malloced;
	bool	*pipes_malloced;
	char	*cmd_err_msg;
	int		valid_cmd_count;
	int		command_err_count;
	int		total_cmd_count;
	int		last_status_code; // para luego poder recuperar el ultimo status code cuando se hace echo $?
}	t_exe;

typedef struct data //aqui iremos agregando todo lo que este alocado.A partir de esta poder acceder a toda la info.
{
	char		**env;
	t_env		*env_list;
	t_dlist		*cmd_list;
	t_exe		exec_info;

	t_int_array	ope_char_i; // @util ?//index of operators characters in string input
	t_int_array	token_separators_char_i; //index of separators characters in string input

	int			nb_chunks; //number of commands and argv separated by operators
}	t_data;

typedef struct s_chunk
{
	char		**tokens; // basic chunks that are taken from line splited by "|"
	char		**argv;
	chunk_type	type;
	////// REDIR FILES //////
	bool		has_redir;
	int			redir_count;
	char		**redir;// list of redir in a chunk ex: > >> >
	int			redir_file_count;
	char		**redir_files;// ex:test ; test1; test2
	int			*file_fd;
	bool		file_fd_malloced;
	bool		*file_open;
	bool		file_open_malloced;
	////// Input redir /////
	bool		has_input_redir;
	int			input_redir_count;
	char		**input_redir;
	int			input_redir_file_count;
	char		**input_redir_file;
	int			*input_file_fd;
	bool		input_file_fd_malloced;
	bool		*input_file_open;
	bool		input_file_open_malloced;
	///////
	bool		has_here_doc;
	//////
	int		chunk_exec_return_status_code; // Not used yet

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
int	create_chunks(char *line,  t_dlist **cmd_list, t_data *data);


/////////////// SRC //////////////
	///////// EXEC/////////
int	main_exec(t_data *data);
int	init_files(t_data *data);
int	listen_heredocs(t_chunk *chunk);

	////// commands init ///
void	init_cmd(t_data *data);
void	clean_cmds_exit(t_data *data, int exit_val);
void	cmd_error_msg(t_data *data, int failure);

	////// path exec ////
void	get_path(char *usr_cmd_input, t_exe *exec_info, t_env *env);

	/////// EXPENSION /////
int	expend_all(t_data *data);
char	*expend_token(t_data *data, char *str);

	///// Tokens /////
t_chunk	*create_token(char ***str, int type, int i, t_quote quotes);
void	set_separator_char_i_struc_arr(char *src, t_int_array *arr);
int		is_seperator(char *src, int i, t_quote *quote);
int		count_redir_files_in_chunks(char **content);

		// operators.c
int		is_operator(char *src, int i, t_quote *quote);
int		count_operador_from_pp_char(char **content);
int		count_operador(char *src);
int		get_operador_index(char *src, t_dlist **cmd_list);
void	init_operador_var(t_quote *quote, int *op_count, int *i);
		// redir and input
int		is_redirection(char *src, int i, t_quote *quote);
int		is_input_redir(char *src, int i, t_quote *quote);
int		count_redir_files_in_chunks(char **content);
int		count_input_files_in_chunks(char **content);
int		count_redir_from_pp_char(char **content);
int		count_input_redir_from_pp_char(char **content);
bool	has_heredoc_from_pp_char(char **content);

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
char	**dup_pp_char(t_data *data, char **substring_arr, int start, int end);

char	*ft_trim(char *src, bool is_malloced);
	//quotes
void	init_quotes(t_quote *quote);
bool	tocken_quote_closed(char *s);
bool	quote_are_closed(t_quote *quote);

// basics
//int		ft_strlen(const char *s);
char	*ft_strdup(char *s);

// custom basics
char	*c_strjoin(char *s1, char *s2, char c);
char	*c_ft_substr(char const *s, unsigned int start, size_t len);

// List Utils
void	free_list(t_dlist *stack_to_free);
void	free_list1(t_dlist **stack_to_free);
int		add_to_list(t_dlist **line, void *content);
void	print_dlist(t_dlist **list);
t_dlist	*find_last_node(t_dlist **lst);
long	stack_lenght(t_dlist **list);

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
void	free_pipes_arr(int **pipe_arr, t_exe *exec_info);



//Temporal for pruebas
int	create_main_chunks(char *src, t_dlist **cmd_list, t_data *data);

#endif
