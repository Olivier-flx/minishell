# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ofilloux <ofilloux@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/14 18:09:50 by sarodrig          #+#    #+#              #
#    Updated: 2025/06/23 16:08:40 by ofilloux         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#     _____    ____    _         ____    _____     _____
#    / ____|  / __ \  | |       / __ \  |  __ \   / ____|
#   | |      | |  | | | |      | |  | | | |__) | | (___
#   | |      | |  | | | |      | |  | | |  _  /   \___ \
#   | |____  | |__| | | |____  | |__| | | | \ \   ____) |
#    \_____|  \____/  |______|  \____/  |_|  \_\ |_____/
#
GREEN	=	\e[1;92m
RED		=	\e[1;91m
DEFAULT	=	\e[0m
YELLOW	=	\e[1;33m


#   __      __             _____    _____              ____    _        ______    _____
#   \ \    / /     /\     |  __ \  |_   _|     /\     |  _ \  | |      |  ____|  / ____|
#    \ \  / /     /  \    | |__) |   | |      /  \    | |_) | | |      | |__    | (___
#     \ \/ /     / /\ \   |  _  /    | |     / /\ \   |  _ <  | |      |  __|    \___ \
#      \  /     / ____ \  | | \ \   _| |_   / ____ \  | |_) | | |____  | |____   ____) |
#       \/     /_/    \_\ |_|  \_\ |_____| /_/    \_\ |____/  |______| |______| |_____/
#
NAME	=	minishell
CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror -g -O0 -I./header

LDFLAGS	=	-lreadline

#INC = -I./header
SIGNALS	=	./src/signals/signals.c \
			./src/signals/sub_proc_sig.c

BUILTINS=	./src/builtins/is_builtin.c \
			./src/builtins/ft_echo.c \
			./src/builtins/ft_export.c \
			./src/builtins/ft_pwd.c \
			./src/builtins/ft_env.c \
			./src/builtins/ft_exit.c\
			./src/builtins/ft_cd.c \
			./src/builtins/ft_unset.c

ENV		=	./src/environment/env_search.c \
			./src/environment/env_utils.c \
			./src/environment/enviro.c \
			./src/environment/env_utils_2.c \
			./src/environment/sort_env.c

TOKENS	=	./src/tokens/user_input_validations/preliminary_checks.c \
			./src/tokens/user_input_validations/incomplete_line.c \
			./src/tokens/user_input_validations/incomplete_line_utils.c \
			./src/tokens/user_input_validations/user_input_validation.c\
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

EXEC	=	./src/exec/exec.c \
			./src/exec/exec_pipex.c \
			./src/exec/commands.c \
			./src/exec/commands_utils.c \
			./src/exec/commands_check_wrong.c \
			./src/exec/path.c \
			./src/exec/listen_heredocs.c \
			./src/exec/pipes.c \
			./src/exec/pipes_close.c \
			./src/exec/execute_builtins.c

FILES	=	./src/exec/files/init_input_files.c \
			./src/exec/files/create_files.c \
			./src/exec/files/close_files.c \
			./src/exec/files/open_files.c \
			./src/exec/files/stdin_stdout.c \
			./src/exec/files/redirects.c

EXPEND	=	./src/exec/Expension/expension.c \
			./src/exec/Expension/expension_tock_len_utils.c \
			./src/exec/Expension/expension_tocken.c \
			./src/exec/Expension/accolades.c \
			./src/exec/Expension/expension_quotes.c \
			./src/exec/Expension/select_from_substring_arr.c \
			./src/exec/Expension/exp_utils.c

UTILS	=	./utils/string/split_quoted.c \
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

SRC		=	main.c \
			$(SIGNALS) \
			$(UTILS) \
			$(BUILTINS) \
			$(TOKENS) \
			$(EXEC) \
			$(FILES) \
			$(EXPEND) \
			$(ENV)


#     ____    ____         _   ______    _____   _______    _____
#    / __ \  |  _ \       | | |  ____|  / ____| |__   __|  / ____|
#   | |  | | | |_) |      | | | |__    | |         | |    | (___
#   | |  | | |  _ <   _   | | |  __|   | |         | |     \___ \
#   | |__| | | |_) | | |__| | | |____  | |____     | |     ____) |
#    \____/  |____/   \____/  |______|  \_____|    |_|    |_____/
#
BUILD_DIR	=	./build
OBJ			=	$(SRC:%.c=$(BUILD_DIR)/%.o)

LIBFT_PATH	=	./libs/libft/libft.a
LIBFT_OBJ	:=	$(patsubst %.c,%.o,$(wildcard ./libs/libft/build/*.c))
#MMD = $(SRC:.c=.d)

#    ______  _____  _       ______      _______         _____    _____  ______  _______  _____
#   |  ____||_   _|| |     |  ____|    |__   __| /\    |  __ \  / ____||  ____||__   __|/ ____|
#   | |__     | |  | |     | |__          | |   /  \   | |__) || |  __ | |__      | |  | (___
#   |  __|    | |  | |     |  __|         | |  / /\ \  |  _  / | | |_ ||  __|     | |   \___ \
#   | |      _| |_ | |____ | |____        | | / ____ \ | | \ \ | |__| || |____    | |   ____) |
#   |_|     |_____||______||______|       |_|/_/    \_\|_|  \_\ \_____||______|   |_|  |_____/
#
$(BUILD_DIR)/%.o	:	%.c $(INC) Makefile
						@printf "$(YELLOW)[minishell] Compiling $< ...$(DEFAULT)                  \r"
						@mkdir -p $(dir $@)
						@$(CC) $(CFLAGS) $(DEBUG) -c $< -o $@

$(NAME) 			:	$(OBJ) $(LIBFT_PATH)
						@$(CC) $(CFLAGS) $(DEBUG) $(OBJ) $(LIBFT_PATH) -o $@ $(LDFLAGS)
						@printf "\n$(GREEN)[minishell] Compiled successfully.$(DEFAULT)\n"

$(LIBFT_PATH)		:	$(LIBFT_OBJ)
						@$(MAKE) -C ./libs/libft
# > /dev/null 2>&1
						@printf "\n$(GREEN)[minishell] libft compiled successfully.$(DEFAULT)\n" > /dev/null
##
# ┌────────────────────────────────────────────┬─────────────────────┬─────────────────┬─────────────────┐
# │ Comando                                    │ ¿Oculta el comando? │ ¿Oculta stdout? │ ¿Oculta stderr? │
# ├────────────────────────────────────────────┼─────────────────────┼─────────────────┼─────────────────┤
# │ $(MAKE) -C ./libs/libft                    │ ❌ No               │ ❌ No          │ ❌ No           │
# │ @$(MAKE) -C ./libs/libft                   │ ✅ Sí               │ ❌ No          │ ❌ No           │
# │ @$(MAKE) -C ./libs/libft > /dev/null       │ ✅ Sí               │ ✅ Sí          │ ❌ No           │
# │ @$(MAKE) -C ./libs/libft > /dev/null 2>&1  │ ✅ Sí               │ ✅ Sí          │ ✅ Sí           │
# └────────────────────────────────────────────┴─────────────────────┴─────────────────┴─────────────────┘

#    _____   _    _   ____   _   _ __     __    _______         _____    _____  ______  _______  _____
#   |  __ \ | |  | | / __ \ | \ | |\ \   / /   |__   __| /\    |  __ \  / ____||  ____||__   __|/ ____|
#   | |__) || |__| || |  | ||  \| | \ \_/ /       | |   /  \   | |__) || |  __ | |__      | |  | (___
#   |  ___/ |  __  || |  | || . ` |  \   /        | |  / /\ \  |  _  / | | |_ ||  __|     | |   \___ \
#   | |     | |  | || |__| || |\  |   | |         | | / ____ \ | | \ \ | |__| || |____    | |   ____) |
#   |_|     |_|  |_| \____/ |_| \_|   |_|         |_|/_/    \_\|_|  \_\ \_____||______|   |_|  |_____/
#
.PHONY: all clean fclean re
.DEFAULT_GOAL = all

all		:	$(NAME)

clean	:
			@make -s clean -C ./libs/libft
			@rm -rf $(BUILD_DIR)
			@printf "$(RED)[minishell] Object files cleaned.$(DEFAULT)\n"

fclean	:	clean
			@make -s fclean -C ./libs/libft
			@rm -f $(NAME)
			@printf "$(RED)[minishell] Cleaned successfully.$(DEFAULT)\n"

re		:	fclean all
