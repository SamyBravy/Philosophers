# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sdell-er <sdell-er@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/16 19:17:18 by sdell-er          #+#    #+#              #
#    Updated: 2024/07/12 11:53:35 by sdell-er         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
# NAME_BONUS = philo_bonus
SRC = ./main.c
# SRC_B = ./main_bonus.c
OBJ = $(SRC:.c=.o)
# OBJ_B = $(SRC_B:.c=.o)
FLAGS = -g -Wall -Wextra -Werror -pthread #-fsanitize=thread
CC = cc

all: $(NAME)

# bonus : $(NAME_BONUS)

$(NAME): $(OBJ)
	@$(CC) $(FLAGS) $(OBJ) -o $(NAME)
	
# $(NAME_BONUS) : $(OBJ_B)
# 	@$(CC) $(FLAGS) $(OBJ_B) -o $(NAME_BONUS)

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(OBJ_B)

fclean: clean
	rm -f $(NAME) $(NAME_BONUS)

re: fclean all

# reboth : fclean all bonus

# rebonus : fclean bonus

.PHONY: all clean fclean re
