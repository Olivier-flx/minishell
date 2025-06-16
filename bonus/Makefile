
COMP = cc

CFLAGS = -Wall -Wextra -Werror

ASTERISK = asterisk/root.c \
		asterisk/replacement_len.c


BONUS_SRC = $(ASTERISK)
HEADER = ./bonus.h

BUILD_DIR = build

BONUS_OBJ = $(BONUS_SRC:.c=.o)
BONUS_OBJ := $(addprefix $(BUILD_DIR)/, $(BONUS_OBJ))

all : $(BONUS_OBJ)

$(BUILD_DIR)/%.o : %.c makefile  $(HEADER)
	mkdir -p $(dir $@)
	@$(COMP) $(CFLAGS) -c $< -o $@

clean :
		rm -f $(BONUS_OBJ)
#		@printf "$(RED)[minishell] Bonus object files cleaned.$(NC)\n"

fclean : clean

re: fclean all

.PHONY : all clean fclean re

