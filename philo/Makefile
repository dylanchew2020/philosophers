# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lchew <lchew@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/14 17:13:24 by lchew             #+#    #+#              #
#    Updated: 2022/05/14 22:01:24 by lchew            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Name:
NAME	=	philo

# MANDATORY SOURCE CODE
SRC_DIR = ./
SRC		= philo.c philo_utils.c philo_utils_2.c philo_thread.c error.c
OBJ_DIR = ./obj/
OBJ		= $(SRC:%.c=$(OBJ_DIR)%.o)

# HEADER
INC_DIR = ./
INC		= -I$(INC_DIR)

# COMPILATION
CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror

# REMOVE FILES OR DIRECTORIES
RM = rm -f
RMDIR = rmdir

# PRETTY
GREEN		=	\e[38;5;118m
YELLOW		=	\e[38;5;226m
RESET		=	\e[0m
_SUCCESS	=	[$(GREEN)SUCCESS$(RESET)]
_INFO		=	[$(YELLOW)INFO$(RESET)]

# [no_of_philo] [time_to_die] [time_to_eat] [time_to_sleep] [no_of_times_each_philo_must_eat]
# - Do not test with more than 200 philosophers
# - Do not test with time_to_die or time_to_eat or time_to_sleep under 60 ms
# INPUT = 1 800 200 200	# the philosopher should not eat and should die!
# INPUT = 5 800 200 200	# no one should die!
# INPUT = 5 800 200 200 7	# no one should die and the simulation should stop when all the philosopher has eaten at least 7 times each.
# INPUT = 4 410 200 200	# no one should die!
INPUT = 4 310 200 100	# a philosopher should die!
# - 2 philosophers and check the different times (a death delayed by more than 10 ms is unacceptable).
# INPUT = 2 310 200 100
# - Test with your values to check all the rules. Check if a philosopher dies at the right time if they don't steal forks, etc.
# INPUT = 105 800 200 200

OUTPUT = print.txt

all: $(NAME)

$(NAME): $(SRC) $(OBJ_DIR) $(OBJ)
	$(CC) $(CFLAGS) $(INC) $(OBJ) -o $@ -fsanitize=address
	@ printf "$(_SUCCESS) Philosophers Program Installation Completed\n\n"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(OBJ_DIR):
	@ mkdir -p $@
	@ printf "$(_INFO) Philosophers object directory created.\n"

run:
	@ ./philo $(INPUT)
	
clean:
	@ $(RM) $(OBJ)
	@ $(RMDIR) $(OBJ_DIR)
	@ printf "$(_INFO) Object files & directory removed.\n"

fclean: clean
	@ $(RM) $(NAME) $(OUTPUT)
	@ printf "$(_INFO) Window cache cleared.\n"

re: fclean all

.PHONY: all clean fclean re
