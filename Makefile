# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aqadil <aqadil@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/16 16:03:35 by aqadil            #+#    #+#              #
#    Updated: 2022/02/23 02:42:44 by aqadil           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minishell
CC		= cc
FLAGS	= -Wall -Wextra -Werror

SRC		= minishell.c ./aqadil/parser.c ./aqadil/ft_split.c ./aqadil/execute.c ./aqadil/ft_strjoin.c ./aqadil/multiple_cmd.c \
			./aqadil/handle_quotes.c \
			./aqadil/handle_quotes_tools.c \
			./aqadil/ft_itoa.c \
			./builtin/cd_tools2.c \
			./builtin/echo.c \
			./builtin/cd.c \
			./builtin/tools.c \
			./builtin/ft_trim.c \
			./builtin/ft_strdup.c \
			./builtin/export.c \
			./builtin/env.c \
			./builtin/pwd.c \
			./builtin/exit.c \
			./builtin/unset.c \
			./signals/disable_signals.c \
			./signals/handle_signals.c \
			./free/free.c \
			./builtin/cd_tools.c \
			./builtin/echo_utils.c \
			./builtin/env_tools.c \
			./builtin/export_tools.c \
			./builtin/tools2.c \
			./signals/enable_signals.c \
			./bonus/and_or.c \
			./bonus/wildcard.c \
			./bonus/tools.c \
			./builtin/cd_tools3.c \
			./builtin/echo_tools4.c \
			./builtin/echo_helper.c \
			./builtin/echo_helper2.c \
			./builtin/echo_helper3.c \
			./builtin/export_tools2.c \
			./builtin/export_tools3.c \
			./builtin/export_tools4.c \
			./builtin/export_tools5.c \
			./builtin/helper_tools.c \
			./aqadil/tools1.c \
			./aqadil/tools2.c \
			./free/garbage_collector.c \
			./bonus/tools2.c \
			./aqadil/str_join_heredoc.c \
			./aqadil/handle_files.c \
			./aqadil/pipe_utils1.c \
			./aqadil/handle_heredoc.c \
			./aqadil/str_str.c \
			./aqadil/pipe_utils.c \
			./aqadil/handle_pipes.c \
			./aqadil/handle_redirections.c \
			my_split.c \
			./aqadil/check_errors.c \
			./aqadil/pipe_splited.c \
			./bonus/tools3.c \
			./aqadil/child_process.c \
			./aqadil/file_utils.c \
			./aqadil/process_redirections.c \
			./aqadil/here_doc_process.c \
			./aqadil/tools4.c \
			./aqadil/tools5.c

OBJ		= minishell.o ./aqadil/parser.o ./aqadil/ft_split.o ./aqadil/execute.o ./aqadil/ft_strjoin.o ./aqadil/multiple_cmd.o \
			./aqadil/handle_quotes.o \
			./aqadil/handle_quotes_tools.o \
			./builtin/echo.o \
			./builtin/cd.o \
			./builtin/tools.o \
			./builtin/ft_trim.o \
			./builtin/ft_strdup.o \
			./builtin/export.o \
			./builtin/env.o \
			./builtin/pwd.o \
			./builtin/exit.o \
			./builtin/unset.o \
			./signals/disable_signals.o \
			./signals/handle_signals.o \
			./free/free.o \
			./builtin/cd_tools.o \
			./builtin/echo_utils.o \
			./builtin/env_tools.o \
			./builtin/export_tools.o \
			./builtin/tools2.o \
			./signals/enable_signals.o \
			./bonus/and_or.o \
			./bonus/wildcard.o \
			./bonus/tools.o \
			./aqadil/ft_itoa.o \
			./builtin/cd_tools2.o \
			./builtin/cd_tools3.o \
			./builtin/echo_tools4.o \
			./builtin/echo_helper.o \
			./builtin/echo_helper2.o \
			./builtin/echo_helper3.o \
			./builtin/export_tools2.o \
			./builtin/export_tools3.o \
			./builtin/export_tools4.o \
			./builtin/export_tools5.o \
			./builtin/helper_tools.o \
			./aqadil/tools1.o \
			./aqadil/tools2.o \
			./free/garbage_collector.o \
			./bonus/tools2.o \
			./aqadil/str_join_heredoc.o \
			./aqadil/handle_files.o \
			./aqadil/pipe_utils1.o \
			./aqadil/handle_heredoc.o \
			./aqadil/str_str.o \
			./aqadil/pipe_utils.o \
			./aqadil/handle_pipes.o \
			./aqadil/handle_redirections.o \
			my_split.o \
			./aqadil/check_errors.o \
			./aqadil/pipe_splited.o \
			./bonus/tools3.o \
			./aqadil/child_process.o \
			./aqadil/file_utils.o \
			./aqadil/process_redirections.o \
			./aqadil/here_doc_process.o \
			./aqadil/tools4.o \
			./aqadil/tools5.o


HEADER	= ./aqadil/minishell.h

$(NAME)	: $(OBJ) $(HEADER)
	$(CC) $(OBJ) ./readline/8.1.2/lib/libreadline.dylib -o $(NAME)
	
all		: $(NAME)

%.o:%.c
	$(CC) $(FLAGS) -o $@ -c $< 

clean	: 
	rm -f $(OBJ)

fclean	: clean
	rm -f $(NAME)

re		: fclean all