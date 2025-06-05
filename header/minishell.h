/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 17:46:36 by ofilloux          #+#    #+#             */
/*   Updated: 2025/06/05 12:44:51 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H


# include <stdio.h> // printf
# include <unistd.h> // write, read, close
					// fork, execve, _exit
					// dup, dup2, pipe
					// isatty, ttyname, ttyslot
# include <stdlib.h> // malloc, free
# include <readline/readline.h>   // readline, rl_clear_history, rl_on_new_line,
								// rl_replace_line, rl_redisplay
# include <readline/history.h>   // add_history
# include <fcntl.h>      // open
# include <sys/stat.h>   // stat, lstat, fstat
# include <sys/types.h>  // stat, lstat, fstat
# include <dirent.h>     // opendir, readdir, closedir
# include <sys/wait.h>   // wait, waitpid, wait3, wait4
# include <signal.h>     // signal, sigaction, sigemptyset, sigaddset, kill
# include <termios.h>    // tcsetattr, tcgetattr
# include <termcap.h>    // tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs
# include <string.h>     // strerror
# include <errno.h>      // set errno
# include <stdio.h>      // perror

# include <stdbool.h>

# include "customs.h"
# include "builtins.h"
# include "../libs/libft/libft.h"

/*
 * ==========================
 *  SIGNAL HANDLING FUNCTIONS
 * ==========================
 */
// Variable global PARA SEÑALES (única permitida)
extern volatile sig_atomic_t g_signal_received;

// Prototipos de funciones de señales
void	handle_signal(int sig);
void	setup_signals(void);
void	handle_ctrl_d(t_data *data);

#endif

/*

 * ==========================
 *  INPUT/OUTPUT FUNCTIONS
 * ==========================
// printf             : Formats and prints data to standard output.
	// int printf(const char *format, ...);
// write              : Writes directly to a file descriptor.
	// ssize_t write(int fd, const void *buf, size_t count);
// read               : Reads directly from a file descriptor.
	// ssize_t read(int fd, void *buf, size_t count);

 * ==========================
 *  MEMORY MANAGEMENT FUNCTIONS
 * ==========================
// malloc             : Dynamically allocates memory.
	// void *malloc(size_t size);
// free               : Frees previously allocated memory.
	// void free(void *ptr);


 * ==========================
 *  INTERACTIVE INPUT FUNCTIONS
 * ==========================
// readline          : Reads a line with an interactive prompt.
	// char *readline(const char *prompt);
// rl_clear_history  : Clears the command history.
	// void rl_clear_history(void);
// rl_on_new_line    : Indicates that a new line is being started.
	// void rl_on_new_line(void);
// rl_replace_line   : Replaces the current line with a new line.
	// void rl_replace_line(const char *text, int clear_undo);
// rl_redisplay      : Refreshes the prompt and current line display.
	// void rl_redisplay(void);
// add_history       : Adds a command to the history.
	// void add_history(const char *line);


 * ==========================
 *  FILE MANAGEMENT FUNCTIONS
 * ==========================
// access             : Checks a file's access permissions.
	// int access(const char *pathname, int mode);
// open               : Opens a file or creates a file descriptor.
	// int open(const char *pathname, int flags, ...);
// close              : Closes an open file descriptor.
	// int close(int fd);
// stat               : Retrieves file information.
	// int stat(const char *pathname, struct stat *statbuf);
// lstat              : Like stat, but does not follow symbolic links.
	// int lstat(const char *pathname, struct stat *statbuf);
// fstat              : Retrieves file information from a file descriptor.
	// int fstat(int fd, struct stat *statbuf);
// unlink             : Deletes a file.
	// int unlink(const char *pathname);
// opendir            : Opens a directory.
	// DIR *opendir(const char *name);
// readdir            : Reads an entry from a directory.
	// struct dirent *readdir(DIR *dirp);
// closedir           : Closes an open directory.
	// int closedir(DIR *dirp);


 * ==========================
 *  PROCESS MANAGEMENT FUNCTIONS
 * ==========================
// fork               : Creates a new child process.
	// pid_t fork(void);
// execve             : Replaces the current process with another program.
	// int execve(const char *pathname, char *const argv[], char *const envp[]);
// exit              : Immediately terminates a process.
	// void _exit(int status);
// wait               : Waits for a child process to finish.
	// pid_t wait(int *status);
// waitpid            : Waits for a specific child process to finish.
	// pid_t waitpid(pid_t pid, int *status, int options);
// wait3              : Waits for a child process and retrieves statistics.
	// pid_t wait3(int *status, int options, struct rusage *rusage);
// wait4              : Like wait3 but provides additional details.
	// pid_t wait4(pid_t pid, int *status, int options, struct rusage *rusage);


 * ==========================
 *  SIGNAL HANDLING FUNCTIONS
 * ==========================
// signal             : Sets a handler for a signal.
	// void (*signal(int signum, void (*handler)(int)))(int);
// sigaction          : Configures actions for a specific signal.
	// int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);
// sigemptyset        : Initializes an empty signal set.
	// int sigemptyset(sigset_t *set);
// sigaddset          : Adds a signal to a set.
	// int sigaddset(sigset_t *set, int signum);
// kill               : Sends a signal to a process.
	// int kill(pid_t pid, int sig);


 * ==========================
 *  STREAM AND REDIRECTION FUNCTIONS
 * ==========================
// dup                : Duplicates a file descriptor.
	// int dup(int oldfd);
// dup2               : Duplicates a file descriptor to a specific descriptor.
	// int dup2(int oldfd, int newfd);
// pipe               : Creates a pipe for interprocess communication.
	// int pipe(int pipefd[2]);


 * ==========================
 *  TERMINAL MANAGEMENT FUNCTIONS
 * ==========================
// isatty             : Checks if a file descriptor is associated with a terminal.
	// int isatty(int fd);
// ttyname            : Returns the name of the terminal for a file descriptor.
	// char *ttyname(int fd);
// ttyslot            : Identifies the position of the terminal in the terminal table.
	// int ttyslot(void);
// tcsetattr          : Configures terminal attributes.
	// int tcsetattr(int fd, int optional_actions, const struct termios *termios_p);
// tcgetattr          : Retrieves terminal attributes.
	// int tcgetattr(int fd, struct termios *termios_p);
// tgetent            : Initializes the terminal database.
	// int tgetent(char *bp, const char *name);
// tgetflag           : Checks a terminal's boolean capability.
	// int tgetflag(const char *id);
// tgetnum            : Retrieves a terminal's numeric capability.
	// int tgetnum(const char *id);
// tgetstr            : Retrieves a terminal's string capability.
	// char *tgetstr(const char *id, char **area);
// tgoto              : Computes a cursor movement position.
	// char *tgoto(const char *cap, int col, int row);
// tputs              : Outputs a string to the terminal with control sequences.
	// int tputs(const char *str, int affcnt, int (*putc)(int));

 * ==========================
 *  ERROR HANDLING FUNCTIONS
 * ==========================
// strerror           : Returns a string describing a given error.
	// char *strerror(int errnum);
// perror             : Prints an error message based on `errno`.
	// void perror(const char *s);

*/
