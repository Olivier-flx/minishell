#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <unistd.h>

// Esta es la única variable global permitida
volatile sig_atomic_t g_signal_received = 0;

// Manejador de señal para SIGINT (Ctrl+C)
void	handle_signal(int sig)
{
	if (sig == SIGINT)
	{
		g_signal_received = 130;
		write(STDOUT_FILENO, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

// Configuración de señales
void	setup_signals(void)
{
	struct sigaction	sa;

	sa.sa_handler = handle_signal;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);

	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
}

// Programa principal de prueba
int	main(void)
{
	char	*input;

	setup_signals();
	while (1)
	{
		input = readline("test-shell$ ");
		if (!input)
		{
			printf("exit\n");
			break;
		}
		if (*input)
		{
			add_history(input);
			printf("Recibido: %s\n", input);
		}
		free(input);
	}
	return (0);
}
