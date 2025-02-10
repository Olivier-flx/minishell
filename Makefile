#COLORS#
GREEN = \033[1;92m
RED = \033[1;91m
NC = \033[0m
YELLOW=\033[1;33m


NAME = mini
CC = cc
CFLAGS = -Wall -Wextra -Werror -g -O0
LDFLAGS = -lreadline

INC = ./header/minishell.h


UTILS = ./utils/string/create_input_token.c \
		./utils/string/ft_split.c \
		./utils/string/basics.c \
		./utils/list/list_utils.c \
		./utils/list/list_free.c \
		./utils/list/list_to_msg.c \
		./utils/msg/error_msg.c \
		./utils/custom_frees.c \
		./src/tokens/operator.c

SRC = main.c \
		$(UTILS)

OBJ = $(SRC:.c=.o)

###################
LIBFT_PATH = ./libs/libft/libft.a

all : $(NAME)

$(NAME) : $(OBJ) $(LIBFT_PATH)
		@$(CC) $(CFLAGS) $(OBJ) $(LIBFT_PATH) -o $@ $(LDFLAGS)
		@printf "$(GREEN)[minishell] Compiled successfully.$(NC)\n"

$(LIBFT_PATH):
		@$(MAKE) -C ./libs/libft > /dev/null 2>&1
		@printf "$(GREEN)[minishell] libft compiled successfully.$(NC)\n"
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
		@$(CC) $(CFLAGS) -c $< -o $@

clean :
		@make -s clean -C ./libs/libft
		rm -f $(OBJ)
		@printf "$(RED)[minishell] Object files cleaned.$(NC)\n"

fclean : clean
		@make -s fclean -C ./libs/libft
		rm -f $(NAME)
		@printf "$(RED)[minishell] Cleaned successfully.$(NC)\n"

re: fclean all

.PHONY: all clean fclean re
