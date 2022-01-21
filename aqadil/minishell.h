/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqadil <aqadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 16:01:17 by aqadil            #+#    #+#             */
/*   Updated: 2022/01/19 17:45:10 by aqadil           ###   ########.fr       */
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

#define STD_INPUT 0
#define STD_OUTPUT 1

typedef struct s_cmd
{
    char *cmd;
    char **args;
    char *type;

    struct s_cmd *next;
} t_cmd;

void parser_and_execute(t_cmd *cmd);
char **ft_split(char const *s, char c);
char *ft_strjoin(char const *s1, char const *s2);
void execute(t_cmd *cmd);

void execute_single_cmd(char *path, char *cmd, char **args);
void execute_single_cmd_handler(char *line);
int cmd_contain(char *str, char c);
void handlle_pipe(char *str);

// builtin
void cd(char *path);
void echo(char *arg);

// tools
int ft_strcmp(const char *s1, const char *s2);
int ft_strlen(char const *s);
char *ft_strtrim(char const *s1, char const *set);
char *ft_strdup(const char *s1);
char *ft_solution(char *line, int pos);

#endif
