/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   customs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 17:26:38 by ofilloux          #+#    #+#             */
/*   Updated: 2025/01/26 10:10:12 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef CUSTOMS
# define CUSTOMS
#endif

typedef struct s_list t_list;

typedef struct data
{
	char		**env;
	t_list		*input;
} t_data;

typedef struct s_list
{
	void				*content;
	struct t_list	*prev;
	struct t_list	*next;
} t_list;

typedef struct s_input_tocken
{
	char	*content;
	bool	is_single_quoted;
	bool	is_double_quoted;
	bool	quote_closed;
	bool	is_var
}

// buildins
int	echo(char string);
int	env(char **env);
int b_exit(int ret_val, t_data data);
int	create_input_token (char *src, t_list **line);





/////////////// UTILS ///////////////
	/////  string //////
// par el shell
int	create_input_to_commands(char *src, t_list **cmd_list);

// basics
int		s_len(const char *s);
char	*s_dup(char *s)


// ERROR
	//MSG
void	simple_error_msg(char *msg);
