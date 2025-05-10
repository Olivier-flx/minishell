#COLORS#
GREEN = \033[1;92m
RED = \033[1;91m
NC = \033[0m
YELLOW=\033[1;33m


NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -g -O0 -I./header

LDFLAGS = -lreadline

#INC = -I./header

BUILTINS = ./src/builtins/ft_echo.c \
		./src/builtins/ft_pwd.c \
		./src/builtins/ft_env.c
		#./src/builtins/ft_exit.c

ENV = ./src/environment/env_search.c \
	./src/environment/env_utils.c \
	./src/environment/enviro.c

TOKENS = ./src/tokens/user_input_validations/user_input_validation.c\
	./src/tokens/user_input_validations/unique_token_operator.c\
	./src/tokens/user_input_validations/double_operators.c \
	./src/tokens/create_input_token.c \
	./src/tokens/operator.c \
	./src/tokens/count_files_in_chunks.c \
	./src/tokens/token_separators.c \
	./src/tokens/create_chunks.c

EXEC = ./src/exec/exec.c \
	./src/exec/create_files.c \
	./src/exec/commands.c \
	./src/exec/path.c \
	./src/exec/free_cmd_exit.c \
	./src/exec/listen_heredocs.c

EXPEND = ./src/exec/Expension/expension.c

UTILS = ./utils/string/ft_split_s.c \
		./utils/string/basics.c \
		./utils/string/custom_basics.c \
		./utils/string/select_from_substring_arr.c \
		./utils/string/quotes.c \
		./utils/string/trim.c \
		./utils/string/ft_split_set_of_char.c \
		./utils/list/list_utils.c \
		./utils/list/list_free.c \
		./utils/list/list_to_msg.c \
		./utils/arrays/methods.c \
		./utils/arrays/arr_frees.c \
		./utils/msg/error_msg.c \
		./utils/custom_frees.c


SRC = main.c \
	$(UTILS) \
	$(BUILTINS) \
	$(TOKENS) \
	$(EXEC) \
	$(EXPEND) \
	$(ENV)

OBJ = $(SRC:.c=.o)

###################
LIBFT_PATH = ./libs/libft/libft.a

all : $(NAME)

$(NAME) : $(OBJ) $(LIBFT_PATH)
		@$(CC) $(CFLAGS) $(DEBUG) $(OBJ) $(LIBFT_PATH) -o $@ $(LDFLAGS)
		@printf "$(GREEN)[minishell] Compiled successfully.$(NC)\n"

$(LIBFT_PATH):
		@$(MAKE) -C ./libs/libft > /dev/null 2>&1
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
		@rm -f $(OBJ)
		@printf "$(RED)[minishell] Object files cleaned.$(NC)\n"

fclean : clean
		@make -s fclean -C ./libs/libft
		@rm -f $(NAME)
		@printf "$(RED)[minishell] Cleaned successfully.$(NC)\n"

re: fclean all

.PHONY: all clean fclean re
