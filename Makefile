# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kotkobay <kotkobay@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/24 11:28:35 by kotkobay          #+#    #+#              #
#    Updated: 2024/10/28 22:09:30 by kotkobay         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
# CFLAGS = -Wall -Wextra -Werror
CFLAGS = -Wall -Wextra -Werror -fsanitize=thread -g3
NAME = philo
SRC = src/main.c src/utils.c src/thread.c src/philosophers_behaiver.c src/mutex.c
OBJ = $(SRC:.c=.o)
all:$(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re