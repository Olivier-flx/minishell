NAME = mini
COMP = cc -Wall -Wextra -Werror -g -O0
INC = ./header/minishell.h
LDFLAGS = -lreadline


UTILS = ./utils/string/create_input_token.c \
		./utils/string/ft_split.c \
		./utils/list/list_utils.c \
		./utils/custom_frees.c

SRC = main.c \
		$(UTILS)

OBJ = $(SRC:.c=.o)

###################

all : $(NAME)

$(NAME) : $(OBJ)
		$(COMP) $(OBJ) -o $(NAME) $(LDFLAGS)

%.o : %.c $(INC) Makefile
		$(COMP) -c $< -o $@

clean :
		rm -f $(OBJ)

fclean : clean
		rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
