# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sdell-er <sdell-er@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/16 19:17:18 by sdell-er          #+#    #+#              #
#    Updated: 2024/07/16 17:30:35 by sdell-er         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_bonus
SRC = ./main_bonus.c ./parsing_bonus.c ./philosopher_bonus.c ./utils_bonus.c ./death_ft_bonus.c
OBJ = $(SRC:.c=.o)
FLAGS = -g -Wall -Wextra -Werror -pthread
CC = cc

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(FLAGS) $(OBJ) -o $(NAME) > /dev/null
	@echo "\e[0;93m[$(NAME)] compiled!\e[0m"

%.o: %.c
	@$(CC) $(FLAGS) -c $< -o $@

clean:
	@rm -f $(OBJ) > /dev/null
	@echo "\e[0;91mcleaned!\e[0m"

fclean: clean
	@rm -f $(NAME) > /dev/null
	@echo "\e[0;91m[$(NAME)] deleted!\e[0m"

re: fclean all

.PHONY: all clean fclean re
