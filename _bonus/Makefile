
CFLAGS = cc -Wall -Wextra -Werror

ASTERISK = ./asterisk/root.c
		./asterisk/replacement_len.c


BONUS_SRC = $(ASTERISK)

HEADER = ./_bonus.h

OBJ = $(SRC:.c=.o)

OBJ_PATH := $(patsubst %.c,%.o,$(wildcard ./build/))

%o : %c makefile  $(HEADER)
	@$(CC) $(CFLAGS) -c $< -o $@

clean :
		@rm -f $(OBJ)
		@printf "$(RED)[minishell] Bonus object files cleaned.$(NC)\n"

fclean : clean
		@printf "$(RED)[minishell] Bonus cleaned successfully.$(NC)\n"

re: fclean all

.PHONY : clean fclean re

