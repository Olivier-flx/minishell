#COLORS#
GREEN = \033[1;92m
RED = \033[1;91m
NC = \033[0m
YELLOW=\033[1;33m


NAME = mini
COMP = cc -Wall -Wextra -Werror -g -O0
INC = ./header/minishell.h
LDFLAGS = -lreadline


UTILS = ./utils/string/create_input_token.c \
		./utils/string/ft_split.c \
		./utils/string/basics.c \
		./utils/list/list_utils.c \
		./utils/list/list_free.c \
		./utils/msg/error_msg.c \
		./utils/custom_frees.c

SRC = main.c \
		$(UTILS)

OBJ = $(SRC:.c=.o)

###################
LIBFT_PATH = ./libs/libft/libft.a
all : .libft $(NAME)

$(NAME) : $(LIBFT_PATH) $(OBJ)
		$(COMP) $(OBJ) $(LIBFT_PATH) -o $(NAME) $(LDFLAGS)
		@printf "\033[1;32m%s\033[0m\n" "[minishell] Compiled successfully."

%.o : %.c $(INC) Makefile
		$(COMP) -c $< -o $@

.libft:
	@make -s -C ./libs/libft DEBUG=$(DEBUG)

clean :
		@make -s clean -C ./libs/libft
		rm -f $(OBJ)
		@printf "\033[1;31m%s\033[0m\n" "[minishell] Object files cleaned."

fclean : clean
		@make -s fclean -C ./libs/libft
		rm -f $(NAME)
		@printf "\033[1;31m%s\033[0m\n" "[minishell] Cleaned successfully."

re: fclean all

.PHONY: all clean fclean re
