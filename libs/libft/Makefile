NAME = libft.a

SRCS = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
	   ft_strlen.c ft_toupper.c ft_tolower.c ft_tolower.c ft_strchr.c \
	   ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c ft_strlcpy.c \
	   ft_strlcat.c ft_memchr.c ft_memcmp.c ft_strncmp.c ft_strrchr.c \
	   ft_strnstr.c ft_atoi.c ft_calloc.c ft_strdup.c ft_putchar_fd.c \
	   ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_striteri.c \
	   ft_strmapi.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_itoa.c ft_split.c \
	   get_next_line_bonus.c get_next_line_utils_bonus.c ft_printf.c \
	   ft_printf_hexa.c ft_printf_hexamin.c ft_printf_numbers.c ft_printf_pointer.c \
	   ft_printf_unsigned_numbers.c ft_printf_strings.c ft_realloc.c


RM	= rm -rf

OBJECTS = $(SRCS:.c=.o)

CFLAGS = -Wall -Werror -Wextra -fPIE
 
%.o: %.c libft.h Makefile
	$(CC) $(CFLAGS) -c $< -o $@ 

all: ${NAME}

${NAME}: ${OBJECTS}
	ar rc ${NAME} ${OBJECTS}
	ranlib ${NAME}  #Ponerle un indice a nuestra libereria (opcional)

clean:
	$(RM) $(OBJECTS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: clean all fclean re
