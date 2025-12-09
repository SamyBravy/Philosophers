# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sdell-er <sdell-er@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/16 19:17:18 by sdell-er          #+#    #+#              #
#    Updated: 2024/07/15 12:48:23 by sdell-er         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
SRC = ./main.c ./philosopher.c ./parsing.c ./philo_utils.c ./check_starvation.c
OBJ = $(SRC:.c=.o)
FLAGS = -g -Wall -Wextra -Werror -pthread
CC = cc

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(FLAGS) $(OBJ) -o $(NAME)
	@echo "\e[0;93m[$(NAME)] compiled!\e[0m"

%.o: %.c
	@$(CC) $(FLAGS) -c $< -o $@

clean:
	@rm -f $(OBJ)
	@echo "\e[0;91mcleaned!\e[0m"

fclean: clean
	@rm -f $(NAME)
	@echo "\e[0;91m[$(NAME)] deleted!\e[0m"


re: fclean all

.PHONY: all clean fclean re
