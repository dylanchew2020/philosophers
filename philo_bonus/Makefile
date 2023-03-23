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
BONUS	=	philo_bonus

# MANDATORY SOURCE CODE
SRC_DIR = ./philo/
SRC		= philo.c philo_utils.c
OBJ_DIR = ./philo/obj/
OBJ		= $(SRC:%.c=$(OBJ_DIR)%.o)

# BONUS SOURCE CODE
BNS_DIR 	= ./philo_bonus/
BNS			= 
BNS_OBJ_DIR = ./philo_bonus/obj/
BNS_OBJ		= $(BNS:%.c=$(BNS_OBJ_DIR)%.o)
BNS_OBJ_ADD	= 


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

all: $(NAME)

$(NAME): $(SRC) $(OBJ_DIR) $(OBJ)
	$(CC) $(CFLAGS) $(INC) $(OBJ) -o $@ -fsanitize=address
	@ printf "$(_SUCCESS) Philosophers Program Installation Completed\n\n"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(OBJ_DIR):
	@ mkdir -p $@
	@ printf "$(_INFO) Philosophers object directory created.\n"
	
$(BONUS): $(CHK_OBJ)
	@ $(CC) $(CFLAGS) $(INC) $(BNS_OBJ) $(BNS_OBJ_ADD) -o $@ -fsanitize=address
	@ printf "$(_SUCCESS) Philosophers Bonus Program Installation Completed\n\n"

$(CHK_OBJ_DIR)%.o: $(CHK_DIR)%.c
	@ $(CC) $(CFLAGS) $(INC) -c $< -o $@

run: #[no_of_philo] [time_to_die] [time_to_eat] [time_to_sleep] [no_of_times_each_philo_must_eat]
	@ ./philo 1 800 200 200
	
clean:
	@ $(RM) $(OBJ) $(BNS_OBJ)
	@ $(RMDIR) $(OBJ_DIR) #$(BNS_OBJ_DIR)
	@ printf "$(_INFO) Object files & directory removed.\n"

fclean: clean
	@ $(RM) $(NAME) $(BONUS)
	@ printf "$(_INFO) Window cache cleared.\n"

re: fclean all

.PHONY: all clean fclean re
