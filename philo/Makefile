# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: avaldin <avaldin@student.42lyon.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/07 15:30:58 by avaldin           #+#    #+#              #
#    Updated: 2024/03/06 08:56:48 by avaldin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

		##		COMPILATION			##

CC			=	cc
FLAGS		=	-Wall -Wextra -Werror -g3

		##		EXECUTABLE			##

NAME		=	philo

		##		PATH				##

SRC_PATH	=	src/
OBJ_PATH	=	.obj/

		##		SOURCES_FILES		##

SOURCES		=	main.c\
				parcing.c\
				process.c\
				process_2.c\
				security.c\
				utils.c\
				ft_atoi.c\
				ft_bzero.c\

HEAD		=	header/philo.h

		##		OBJECTS				##

OBJS		=	$(SOURCES:%.c=$(OBJ_PATH)%.o)

		##		RULES				##


all			:	$(NAME)
$(OBJS)		:	$(OBJ_PATH)%.o : $(SRC_PATH)%.c $(HEADER) Makefile
	$(CC) $(FLAGS) -c $< -o $@

$(NAME)		:	$(OBJ_PATH) $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o $(NAME) -lpthread

$(OBJ_PATH)	:
	@mkdir -p $(OBJ_PATH)

clean		:
	rm -rf $(OBJ_PATH)

fclean		:	clean
	rm -f $(NAME)

re        :    fclean all
.PHONY    :    all clean fclean re