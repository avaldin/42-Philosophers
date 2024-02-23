# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: avaldin <avaldin@student.42lyon.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/07 15:30:58 by avaldin           #+#    #+#              #
#    Updated: 2024/02/23 11:09:14 by avaldin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

		##		COMPILATION			##

CC			=	cc
FLAGS		=	-Wall -Wextra -Werror -g3 -O3

		##		EXECUTABLE			##

NAME		=	philo

		##		PATH				##

SRC_PATH	=	src
OBJ_PATH	=	obj

		##		SOURCES_FILES		##

SOURCES		=	src/main.c\
				src/parcing.c\
				src/process.c\
				src/security.c\
				src/libft/ft_atoi.c\

HEADER		=	header/philo.h\

		##		OBJECTS				##

OBJS		=	$(SOURCES:.c=.o)

		##		RULES				##


all			:	$(NAME)
%.o			:	%.c $(HEADER)
	$(CC) $(FLAGS) -c $< -o $@

$(NAME)		:	$(OBJS) Makefile
	$(CC) $(OBJS) -o $(NAME)

clean		:
	rm -f $(OBJS)

fclean		:	clean
	rm -f $(NAME)

re        :    fclean all
.PHONY    :    all clean fclean re