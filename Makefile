# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sdell-er <sdell-er@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/16 19:17:18 by sdell-er          #+#    #+#              #
#    Updated: 2024/03/12 17:44:43 by sdell-er         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philos
# NAME_BONUS = philo_bonus
SRC = ./philo/main.c
# SRC_B = ./philo_bonus/main_bonus.c
OBJ = $(SRC:.c=.o)
# OBJ_B = $(SRC_B:.c=.o)
FLAGS = -g -Wall -Wextra -Werror
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
	@rm -f $(OBJ) #$(OBJ_B)

fclean: clean
	@rm -f $(NAME) #$(NAME_BONUS)

re: fclean all

# reboth : fclean all bonus

# rebonus : fclean bonus

.PHONY: all clean fclean re
