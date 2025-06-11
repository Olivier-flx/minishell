
FLAGS = -Wall -Werror -Wextra

NAME = libft.a

BONUS_SRC = ft_lstnew_bonus.c \
	ft_lstadd_front_bonus.c \
	ft_lstsize_bonus.c \
	ft_lstlast_bonus.c \
	ft_lstadd_back_bonus.c \
	ft_lstdelone_bonus.c \
	ft_lstclear_bonus.c \
	ft_lstiter_bonus.c \
	ft_lstmap_bonus.c

SRC = ft_atoi.c \
	ft_bzero.c \
	ft_calloc.c \
	ft_isalnum.c \
	ft_isalpha.c \
	ft_isascii.c \
	ft_isdigit.c \
	ft_isprint.c \
	ft_itoa.c \
	ft_memchr.c \
	ft_memcmp.c \
	ft_memcpy.c \
	ft_memmove.c \
	ft_memset.c \
	ft_putchar_fd.c \
	ft_putendl_fd.c \
	ft_putnbr_fd.c \
	ft_putstr_fd.c \
	ft_split.c \
	ft_strchr.c \
	ft_strdup.c \
	ft_striteri.c \
	ft_strjoin.c \
	ft_strlcat.c \
	ft_strlcpy.c \
	ft_strlen.c \
	ft_strmapi.c \
	ft_strcmp.c	ft_strncmp.c \
	ft_strnstr.c \
	ft_strrchr.c \
	ft_strtrim.c \
	ft_substr.c \
	ft_tolower.c \
	ft_toupper.c \
	$(BONUS_SRC)

OBJ = $(SRC:.c=.o)

OBJ_BONUS = $(BONUS_SRC:.c=.o)

all : $(NAME)

$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)
	@ranlib $(NAME)
# ranlib Met à jour l'index (sommaire) de l'archive pour
# permettre au linker de trouver rapidement les symboles
# (fonctions/variables) lors de la compilation.
# plus rapide, plus robust

%.o: %.c libft.h Makefile
	cc $(FLAGS) -c $< -o $@

bonus : ${NAME} $(OBJ_BONUS)
	ar rcs $(NAME) $(OBJ_BONUS)

clean:
	rm -f $(OBJ) $(OBJ_BONUS)

fclean: clean
	rm -f $(NAME)

re : fclean all

.PHONY: all, clean, fclean, re, bonus
