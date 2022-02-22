# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aqadil <aqadil@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/16 16:03:35 by aqadil            #+#    #+#              #
#    Updated: 2022/02/11 18:34:28 by ahaifoul         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minishell
CC		= cc
FLAGS	= -g -Wall -Wextra -Werror

SRC		= minishell.c ./aqadil/parser.c ./aqadil/ft_split.c ./aqadil/str_join_heredoc.c ./aqadil/handle_files.c ./aqadil/pipe_utils1.c ./aqadil/get_next_line.c ./aqadil/get_next_line_utils.c ./aqadil/handle_heredoc.c ./aqadil/execute.c ./aqadil/str_str.c ./aqadil/op_split.c ./aqadil/pipe_utils.c ./aqadil/handle_pipes.c ./aqadil/handle_redirections.c ./aqadil/ft_strjoin.c ./aqadil/multiple_cmd.c \
			./builtin/echo.c \
			./builtin/cd.c \
			./builtin/tools.c \
			./builtin/ft_trim.c \
			./builtin/ft_strdup.c \
			my_split.c 
OBJ		= minishell.o ./aqadil/parser.o ./aqadil/ft_split.o ./aqadil/execute.o ./aqadil/str_join_heredoc.o ./aqadil/pipe_utils1.o ./aqadil/get_next_line.o ./aqadil/get_next_line_utils.o  ./aqadil/handle_files.o ./aqadil/handle_heredoc.o ./aqadil/pipe_utils.o  ./aqadil/op_split.o ./aqadil/str_str.o ./aqadil/handle_pipes.o ./aqadil/handle_redirections.o ./aqadil/ft_strjoin.o ./aqadil/multiple_cmd.o \
			./builtin/echo.o \
			./builtin/cd.o \
			./builtin/tools.o \
			./builtin/ft_trim.o \
			./builtin/ft_strdup.o \
			my_split.o 

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
