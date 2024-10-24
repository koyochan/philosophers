# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kotkobay <kotkobay@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/24 11:28:35 by kotkobay          #+#    #+#              #
#    Updated: 2024/10/24 11:29:36 by kotkobay         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g3
NAME = philo
PRINTF_DIR = ft_printf
SRC = src/main.c src/utils.c src/thread.c
OBJ = $(SRC:.c=.o)
all:$(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@


$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) 


clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re