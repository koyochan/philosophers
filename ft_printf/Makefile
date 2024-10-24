NAME = libftprintf.a

CC = cc
CFLAG = -Wall -Wextra -Werror
SRC = ft_itoa.c libftprintf.c printf_d.c printf_p.c printf_s.c printf_u.c printf_x.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)

%.o: %.c
	$(CC) $(CFLAG) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re