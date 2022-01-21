# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aqadil <aqadil@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/16 16:03:35 by aqadil            #+#    #+#              #
#    Updated: 2022/01/19 01:56:57 by aqadil           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minishell
CC		= cc
FLAGS	= -Wall -Wextra -Werror

SRC		= minishell.c ./aqadil/parser.c ./aqadil/ft_split.c ./aqadil/execute.c ./aqadil/handle_pipes.c ./aqadil/ft_strjoin.c ./aqadil/multiple_cmd.c \
			./builtin/echo.c \
			./builtin/cd.c \
			./builtin/tools.c \
			./builtin/ft_trim.c \
			./builtin/ft_strdup.c
OBJ		= minishell.o ./aqadil/parser.o ./aqadil/ft_split.o ./aqadil/execute.o ./aqadil/handle_pipes.o ./aqadil/ft_strjoin.o ./aqadil/multiple_cmd.o \
			./builtin/echo.o \
			./builtin/cd.o \
			./builtin/tools.o \
			./builtin/ft_trim.o \
			./builtin/ft_strdup.o

HEADER	= ./aqadil/minishell.h

$(NAME)	: $(OBJ) $(HEADER)
	$(CC) $(OBJ) -lreadline -o $(NAME)
	
all		: $(NAME)

%.o:%.c
	$(CC) -o $@ -c $<

clean	: 
	rm -f $(OBJ)

fclean	: clean
	rm -f $(NAME)

re		: fclean all