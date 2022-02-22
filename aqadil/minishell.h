/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqadil <aqadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 16:01:17 by aqadil            #+#    #+#             */
/*   Updated: 2022/02/03 16:29:34 by aqadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <string.h>
#include <fcntl.h>

#define STD_INPUT 0
#define STD_OUTPUT 1

#define BUFFER_SIZE 100000

typedef struct s_cmd
{
    char *cmd;
    char **args;
    char *type;

    struct s_cmd *next;
} t_cmd;

void parser_and_execute(t_cmd *cmd);
char **ft_split(char const *s, char c);
char *ft_strjoin(char const *s1, char *s2);
void execute(t_cmd *cmd);

void execute_single_cmd(char *path, char *cmd, char **args);
void execute_single_cmd_handler(char *line);
int cmd_contain(char *str, char c);

void handlle_pipe(char *str);
char *op_strjoin(char const *s1, char const *s2);
int str_len(char const *str);
void handlle_redirections(char *str);
void execute_cmd(char *str);
int check_access(char *str);
char **op_split(char *str, char *charset);
char *str_str(char *str, char *to_find);
int get_infile_fd(char *str);
int open_files_appe(char *str);
int open_files(char *str);
char *get_cmd_heredoc(char *str);
char *get_cmmd(char *str);
int handle_heredoc(char *str);
char **get_path(void);
void execute_cmd_without_redirect(char **parsed_pipe, int index, int fd_old_input, int fd_heredoc);
void check_acces(char *str);
int *check_str(char *str);
char *get_cmd(char *str);
void redirect_input(char **parsed_pipe, int i, int *fd_pp);
char *splt_str(char *str, char c, char *red);
int not_contain(char *str, char c);
void handle_fd_error(int f1);
int escape_cmd_open_file(char *str);
int only_rd_fd(char *str);
int only_open_append(char *str);
int only_open(char *str, char c);
int append_to_first_file(char *str);
int special_open_for_append(char *str);
int get_fd_input(char *str);
char *str_join_heredoc(char *s1, char *s2);
int open_heredoc(char *str);
int open_files_heredoc(char *str);
int open_another_heredoc(char *str_heredoc);
void execute_cmd_heredoc(char *str, int fd_heredoc);
int *get_heredoc_content(char *str);

char *get_cmd_heredoc(char *str);
char *get_delimetr(char *str);

//get_next_line
#include <unistd.h>

char *get_next_line(int fd);
char *ft_strjoin_g(char *s1, char *s2);
char *ft_strdup(char const *s1);
int ft_strchr(const char *s, int c);
char *ft_substr(char *s, unsigned int start, size_t len);
int str_len(const char *str);

//

// builtin
void cd(char *path);
void echo(char *arg);

// tools
int ft_strcmp(const char *s1, const char *s2);
int ft_strlen(char const *s);
char *ft_strtrim(char const *s1, char const *set);
char *ft_strdup(const char *s1);
char *ft_solution(char *line, int pos);
char **ft_split22(char *s, char *set);

#endif
