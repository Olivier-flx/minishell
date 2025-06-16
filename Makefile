#     _____    ____    _         ____     _____     _____
#    / ____|  / __ \  | |       / __ \   |  __ \   / ____|
#   | |      | |  | | | |      | |  | |  | |__) | | (___
#   | |      | |  | | | |      | |  | |  |  _  /   \___ \
#   | |____  | |__| | | |____  | |__| |  | | \ \   ____) |
#    \_____|  \____/  |______|  \____/   |_|  \_\ |_____/
#

GREEN = \033[1;92m
RED = \033[1;91m
NC = \033[0m
YELLOW=\033[1;33m

#     _____    ____    __  __   _____    _____    _
#    / ____|  / __ \  |  \/  | |  __ \  |_   _|  | |
#   | |      | |  | | | \  / | | |__) |   | |    | |
#   | |      | |  | | | |\/| | |  ___/    | |    | |
#   | |____  | |__| | | |  | | | |       _| |_   | |____
#    \_____|  \____/  |_|  |_| |_|      |_____|  |______|
#

NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -g -O0 -I./header

LDFLAGS = -lreadline

#INC = -I./header

#    ______   _____   _        ______    _____
#   |  ____| |_   _| | |      |  ____|  / ____|
#   | |__      | |   | |      | |__    | (___
#   |  __|     | |   | |      |  __|    \___ \
#   | |       _| |_  | |____  | |____   ____) |
#   |_|      |_____| |______| |______| |_____/
#

SIGNALS = ./src/signals/signals.c \
		./src/signals/sub_proc_sig.c

BUILTINS = ./src/builtins/is_builtin.c \
		./src/builtins/ft_echo.c \
		./src/builtins/ft_export.c \
		./src/builtins/ft_pwd.c \
		./src/builtins/ft_env.c \
		./src/builtins/ft_exit.c\
		./src/builtins/ft_cd.c \
		./src/builtins/ft_unset.c

ENV = ./src/environment/env_search.c \
		./src/environment/env_utils.c \
		./src/environment/enviro.c \
		./src/environment/env_utils_2.c \
		./src/environment/sort_env.c

TOKENS = ./src/tokens/user_input_validations/preliminary_checks.c \
		./src/tokens/user_input_validations/check_line.c \
		./src/tokens/user_input_validations/incomplete_line.c \
		./src/tokens/user_input_validations/user_input_validation.c\
		./src/tokens/user_input_validations/check_tokens.c \
		./src/tokens/user_input_validations/check_tokens_utils.c \
		./src/tokens/user_input_validations/check_pipe_utils.c \
		./src/tokens/user_input_validations/unique_token_operator.c\
		./src/tokens/user_input_validations/double_operators.c \
		./src/tokens/create_input_token.c \
		./src/tokens/operator.c \
		./src/tokens/operator_arr.c \
		./src/tokens/operator_utils.c \
		./src/tokens/count_files_in_chunks.c \
		./src/tokens/init_file_arr.c \
		./src/tokens/token_separators.c \
		./src/tokens/create_argv.c \
		./src/tokens/create_argv_utils.c \
		./src/tokens/create_chunks.c

EXEC = ./src/exec/exec.c \
		./src/exec/exec_pipex.c \
		./src/exec/commands.c \
		./src/exec/commands_utils.c \
		./src/exec/commands_check_wrong.c \
		./src/exec/path.c \
		./src/exec/listen_heredocs.c \
		./src/exec/pipes.c \
		./src/exec/pipes_close.c \
		./src/exec/execute_builtins.c

FILES = ./src/exec/files/init_input_files.c \
		./src/exec/files/create_files.c \
		./src/exec/files/close_files.c \
		./src/exec/files/open_files.c \
		./src/exec/files/stdin_stdout.c \
		./src/exec/files/redirects.c

EXPEND = ./src/exec/Expension/expension.c \
		./src/exec/Expension/expension_tock_len_utils.c \
		./src/exec/Expension/expension_tocken.c \
		./src/exec/Expension/accolades.c \
		./src/exec/Expension/expension_quotes.c \
		./src/exec/Expension/select_from_substring_arr.c \
		./src/exec/Expension/exp_utils.c

UTILS = ./utils/string/split_quoted.c \
		./utils/string/split_quoted_utils.c \
		./utils/string/basics.c \
		./utils/string/custom_basics.c \
		./utils/string/quotes.c \
		./utils/string/quotes_2.c \
		./utils/string/trim.c \
		./utils/string/ft_split_set_of_char.c \
		./utils/string/ft_split_sgmt_count.c \
		./utils/list/list_utils.c \
		./utils/list/list_free.c \
		./utils/list/list_to_msg.c \
		./utils/arrays/methods.c \
		./utils/arrays/arr_frees.c \
		./utils/msg/error_msg.c \
		./utils/frees/custom_frees.c \
		./utils/frees/free_resources.c \
		./utils/frees/free_exec_info.c


SRC = main.c \
	$(SIGNALS) \
	$(UTILS) \
	$(BUILTINS) \
	$(TOKENS) \
	$(EXEC) \
	$(FILES) \
	$(EXPEND) \
	$(ENV)

#     ____    ____         _         __    _        _____   ____     _____
#    / __ \  |  _ \       | |       / /   | |      |_   _| |  _ \   / ____|
#   | |  | | | |_) |      | |      / /    | |        | |   | |_) | | (___
#   | |  | | |  _ <   _   | |     / /     | |        | |   |  _ <   \___ \
#   | |__| | | |_) | | |__| |    / /      | |____   _| |_  | |_) |  ____) |
#    \____/  |____/   \____/    /_/       |______| |_____| |____/  |_____/
#

OBJ = $(SRC:.c=.o)

LIBFT_OBJ := $(patsubst %.c,%.o,$(wildcard ./libs/libft/*.c))
#MMD = $(SRC:.c=.d)

###################
LIBFT_PATH = ./libs/libft/libft.a

#    ____     ____    _   _   _    _    _____
#   |  _ \   / __ \  | \ | | | |  | |  / ____|
#   | |_) | | |  | | |  \| | | |  | | | (___
#   |  _ <  | |  | | | . ` | | |  | |  \___ \
#   | |_) | | |__| | | |\  | | |__| |  ____) |
#   |____/   \____/  |_| \_|  \____/  |_____/
#

BONUS_PATH = ./_bonus

B_HEADER = $(BONUS_PATH)/_bonus.h

B_MAKEFILE = $(BONUS_PATH)/Makefile

B_OBJ := $(patsubst %.c,%.o,$(wildcard $(BONUS_PATH)/))

#     _____   __  __   _____         __   _____    ______   _____     _____
#    / ____| |  \/  | |  __ \       / /  |  __ \  |  ____| |  __ \   / ____|
#   | |      | \  / | | |  | |     / /   | |  | | | |__    | |__) | | (___
#   | |      | |\/| | | |  | |    / /    | |  | | |  __|   |  ___/   \___ \
#   | |____  | |  | | | |__| |   / /     | |__| | | |____  | |       ____) |
#    \_____| |_|  |_| |_____/   /_/      |_____/  |______| |_|      |_____/
#

all : $(NAME)

$(NAME) : $(OBJ) $(LIBFT_PATH)
		@$(CC) $(CFLAGS) $(DEBUG) $(OBJ) $(LIBFT_PATH) -o $@ $(LDFLAGS)
		@printf "$(GREEN)[minishell] Compiled successfully.$(NC)\n"

$(LIBFT_PATH): $(LIBFT_OBJ)
		@$(MAKE) -C ./libs/libft
#> /dev/null 2>&1
		@printf "$(GREEN)[minishell] libft compiled successfully.$(NC)\n" > /dev/null
##
# ┌────────────────────────────────────────────┬─────────────────────┬─────────────────┬─────────────────┐
# │ Comando                                    │ ¿Oculta el comando? │ ¿Oculta stdout? │ ¿Oculta stderr? │
# ├────────────────────────────────────────────┼─────────────────────┼─────────────────┼─────────────────┤
# │ $(MAKE) -C ./libs/libft                    │ ❌ No               │ ❌ No          │ ❌ No           │
# │ @$(MAKE) -C ./libs/libft                   │ ✅ Sí               │ ❌ No          │ ❌ No           │
# │ @$(MAKE) -C ./libs/libft > /dev/null       │ ✅ Sí               │ ✅ Sí          │ ❌ No           │
# │ @$(MAKE) -C ./libs/libft > /dev/null 2>&1  │ ✅ Sí               │ ✅ Sí          │ ✅ Sí           │
# └────────────────────────────────────────────┴─────────────────────┴─────────────────┴─────────────────┘



%.o : %.c $(INC) Makefile
		@$(CC) $(CFLAGS) $(DEBUG) -c $< -o $@

clean :
		@make -s clean -C ./libs/libft
		@make -s clean -C ./_bonus
		@rm -f $(OBJ)
		@printf "$(RED)[minishell] Object files cleaned.$(NC)\n"

fclean : clean
		@make -s fclean -C ./libs/libft
		@make -s fclean -C ./_bonus
		@rm -f $(NAME)
		@printf "$(RED)[minishell] Cleaned successfully.$(NC)\n"

re: fclean all

bonus : ${NAME} $(B_HEADER) $(B_MAKEFILE) $(B_OBJ) $(OBJ) $(LIBFT_PATH)
	make -C ./_bonus
	@$(CC) $(CFLAGS) $(DEBUG) $(OBJ) $(B_OBJ) $(LIBFT_PATH) -o $@ $(LDFLAGS)
	@printf "$(GREEN)[minishell] Bonus compiled successfully.$(NC)\n"

.PHONY: all clean fclean re bonus

#
##
#### Text ART : https://patorjk.com/software/taag/#p=display&c=bash&f=Big
##
#
