# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: avaldin <avaldin@student.42lyon.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/07 15:30:58 by avaldin           #+#    #+#              #
#    Updated: 2024/02/28 12:05:03 by avaldin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

		##		COMPILATION			##

CC			=	cc
FLAGS		=	-Wall -Wextra -Werror -D_REENTRANT -g3

		##		EXECUTABLE			##

NAME		=	philo

		##		PATH				##

SRC_PATH	=	src
OBJ_PATH	=	obj

		##		SOURCES_FILES		##

SOURCES		=	src/main.c\
				src/parcing.c\
				src/process.c\
				src/process_2.c\
				src/security.c\
				src/mutex.c\
				src/libft/ft_atoi.c\
				src/libft/ft_bzero.c\

HEADER		=	header/philo.h\

		##		OBJECTS				##

OBJS		=	$(SOURCES:.c=.o)

		##		RULES				##


all			:	$(NAME)
%.o			:	%.c $(HEADER)
	$(CC) $(FLAGS) -c $< -o $@

$(NAME)		:	$(OBJS) Makefile
	$(CC) $(OBJS) -o $(NAME) -lpthread

clean		:
	rm -f $(OBJS)

fclean		:	clean
	rm -f $(NAME)

re        :    fclean all
.PHONY    :    all clean fclean re