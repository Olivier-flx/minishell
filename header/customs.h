/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   customs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 17:26:38 by ofilloux          #+#    #+#             */
/*   Updated: 2025/05/12 22:22:28 by ofilloux         ###   ########.fr       */
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

//# include "builtins.h"

typedef struct	s_env t_env;

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

/* typedef struct	s_env
{
	char	*key;
	char	*value;
	bool	is_exported; //1 = in ENV, if 0 --> global variable
	struct	s_env *next;
}	t_env; */

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
	bool	has_msg;
	int		valid_cmd_count;
	int		command_err_count;
	int		total_cmd_count;
	int		last_status_code; // para luego poder recuperar el ultimo status code cuando se hace echo $?
}	t_exe;

typedef struct s_data //aqui iremos agregando todo lo que este alocado.A partir de esta poder acceder a toda la info.
{
	char		**env;
	t_env		*env_list;
	char		*line;
	t_dlist		*cmd_list;
	t_exe		exec_info;
	t_int_array	ope_char_i; // @util ?//index of operators characters in string input
	t_int_array	token_separators_char_i; //index of separators characters in string input
	int			exit_status;

	int			nb_chunks; //number of commands and argv separated by operators
}	t_data;

typedef struct s_chunk
{
	char		**tokens; // basic chunks that are taken from line splited by "|"
	char		**argv;
	char		*argv_0_nopath; // store the cmd as it was written by the user
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
	int			**heredoc_pipe_arr;
	bool		heredoc_pipe_arr_malloced;
	bool		*pipes_malloced;
	int			nb_heredocs;
	//////
	int			chunk_exec_return_status_code; // Not used yet

	int			index; // util ?
	int			len; // util ?
	t_quote		quotes; // util ?
}	t_chunk;


/////////////// SRC //////////////
void	signal_handlers_for_readline(t_data *data);

/*
 * ==========================
 * 			EXEC
 * ==========================
 */
int		main_exec(t_data *data);
int		listen_heredocs(t_data *data, t_chunk *chunk);
bool	is_builtin(char *cmd);
int		run_builtins(t_data *data, t_exe *exe, t_chunk *chunk, int i);
int		execve_builtin_in_child(t_data *data, t_exe *exe, t_chunk *chunk, int i);

	////// commands init ///
void	init_cmd(t_data *data);
void	clean_exec_info(t_data *data, int exit_val);
void	cmd_error_msg(t_data *data, int failure);

	////// path exec ////
void	get_path(char *usr_cmd_input, t_exe *exec_info, t_env *env);
int		usr_input_got_slash(char *str);

	////// PIPES ///////
void	close_unecessary_pipes(t_exe *exe, int i);
void	close_all_pipes(t_exe *exe, int ***pipe_arr);
void	init_pipes_2arr(t_data *data, t_exe *exe);
void	init_bool_pipes_malloced(t_data * data, t_exe *exe_info);
void	init_pipes_2arr_for_heredoc(t_data *data, t_chunk *chunk);
void	close_heredocs_pipes(t_chunk * chunk);

/// FILES
int		init_files(t_data *data);
int		init_input_files(t_data *data);
	// files redirects //
void	redirect_input_file(t_data *data, t_chunk *chunk);
void	redirect_to_output_file(t_data *data, t_chunk *chunk);
	// files management
void	close_files(t_chunk *chunk);
void	close_files_if_opened(int *fd_arr, bool *file_open, int len);

//// EXPENSION /////
int		expend_all(t_data *data);
char	*expend_token(t_data *data, char *str);
char	*get_var_name_in_accolade(char *str, int i);

	/////  /////
/*
 * ==========================
 * 		  Tokeninzation
 * ==========================
 */
// verifications //
			//user_input_validation
void	listen_incomplete_lines(t_data *data,char **line);
int	check_for_user_input_error(t_dlist **cmd_list);
int	check_for_triple(t_dlist **cmd_list);
int	check_for_simple(t_dlist **cmd_list);
int	line_accolade_closed(char *line);

			//system_input_validation
void	check_system_input_error(t_data *data, t_dlist **cmd_list); // Unused.

/// Chunks & segments
int		create_chunks(char *line,  t_dlist **cmd_list, t_data *data);
int		create_main_chunks(char *src, t_dlist **cmd_list, t_data *data);
t_chunk	*create_token(char ***str, chunk_type type, int i, t_quote quotes);
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
int		count_heredocs_in_chunks(char **content);
bool	has_heredoc_from_pp_char(char **content);


		//cleaning.c
void	set_ope_char_i_struc_arr(char *src, t_int_array *arr);
void	set_ope_char_i_arr(char *src, t_int_array *arr);


int		create_input_to_commands(char *src, t_dlist **cmd_list, t_data *data);


/////////////// UTILS ///////////////
/*
 * ==========================
 * 			STRINGS
 * ==========================
 */
void	quote_increment(char *src, int i, t_quote *quote);
char	**split_quoted(char const *s, char c);// @legacy
char	**split_quoted2(char *s,t_data *data);
char	**dup_pp_char(t_data *data, char **substring_arr, int start, int end);
char	*ft_trim(char *src, bool is_malloced);
	//quotes
void	init_quotes(t_quote *quote);
bool	tocken_quote_closed(char *s);
bool	quote_are_closed(t_quote *quote);
bool	quote_and_acc_are_closed(t_quote *quote);
	// custom basics
char	*c_strjoin(char *s1, char *s2, char c);
char	*c_ft_substr(char const *s, unsigned int start, size_t len);


/*
 * ==========================
 * 	   dbl List Utils
 * ==========================
 */
void	free_list(t_dlist *stack_to_free);
void	free_list1(t_dlist **stack_to_free);
int		add_to_list(t_dlist **line, void *content);
void	print_dlist(t_dlist **list);
t_dlist	*find_last_d_node(t_dlist **lst);
long	stack_lenght(t_dlist **list);
void	print_int_arr(t_int_array *arr);
void	print_pp_char_arr(char **str);


/*
 * ==========================
 * 	   ARRAYS
 * ==========================
 */
// arrays
bool	int_var_in_arr(int var, t_int_array *arr);
int		pp_char_len(char **array);
// arrays_free
void	ft_free(void ** ptr);
void	free_av(char ***av);
char	**free_uncomplete_av(char **av, int i);

/*
 * ==========================
 * 	   ERRORS & MSG
 * ==========================
 */
// ERROR
	//MSG
void	simple_error_msg(char *msg);
void debug_print_cmd_list(t_dlist **cmd_list_ptr); //@debug

/*
 * ==========================
 * 	   FREE & EXITS
 * ==========================
 */
// FREES
void	free_resources(t_data *data, bool clear_env, bool free_line);
void	free_cmdlist(t_dlist *cmd_list);
void	free_pipes_arr(int **pipe_arr, t_exe *exec_info);

#endif
