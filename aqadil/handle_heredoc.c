/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaifoul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 11:23:58 by ahaifoul          #+#    #+#             */
/*   Updated: 2022/02/08 11:24:12 by ahaifoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int cmdo_contain(char *str, char c)
// {
//     int i = 0;
//     if (str[i] == c)
//     {
//         while (str[i])
//             i++;
//         if (str[i - 1] == c)
//             return (1);
//     }
//     return (0);
// }
// char *check_temp(char *str)
// {
//     char *temp;

//     temp = ft_strtrim(str, " ");

//     if (cmdo_contain(temp, '"'))
//         temp = ft_strtrim(temp, "\"");
//     else if (cmdo_contain(temp, '\''))
//         temp = ft_strtrim(temp, "\'");

//     /*printf("%s\n", temp);
//     exit(0);*/
//     return (temp);
// }
int t_str_len(char **str)
{
    int i;

    i = 0;
    while (str[i])
        i++;
    return (i);
}

void execute_cmd_heredoc(char *str, int fd_heredoc)
{
    char *cmd;
    int f2;
    int pid;

    cmd = get_cmd_heredoc(str);
    dup2(fd_heredoc, STD_INPUT);
    close(fd_heredoc);
    f2 = open_files_heredoc(str);
    if (not_contain(str, '>') || str_str(str, ">>"))
    {
        dup2(f2, STD_OUTPUT);
        close(f2);
    }
    pid = fork();
    if (pid == -1)
        return (perror("Fork error"));
    if (pid == 0)
        execute_cmd(cmd);
    else
        waitpid(-1, 0, 0);
    exit(0);
}

int open_heredoc(char *str_heredoc)
{
    char **spltd_str;
    int i;
    char *del;
    char *line = NULL;
    int fd_pipe[2];
    char *temp1 = NULL;

    i = 1;
    spltd_str = ft_split22(str_heredoc, "<<");
    pipe(fd_pipe);
    while (spltd_str[i])
    {
        del = get_delimetr(spltd_str[i]);
        line = readline("-> heredoc: ");
        while (line)
        {
            if (strcmp(line, del) == 0)
                break;
            if (spltd_str[i + 1] == NULL)
                temp1 = str_join_heredoc(temp1, line);
            line = readline("-> heredoc: ");
        }
        i++;
    }
    temp1 = ft_strjoin(temp1, "\n");
    write(fd_pipe[1], temp1, str_len(temp1));
    close(fd_pipe[1]);
    return (fd_pipe[0]);
}

int open_files_heredoc(char *str)
{
    int f1 = -1;
    char **spltd_str;
    int i = 0;

    spltd_str = ft_split22(str, "<<");
    while (spltd_str[i])
    {
        if (not_contain(spltd_str[i], '>') || str_str(spltd_str[i], ">>") || not_contain(spltd_str[i], '<'))
            f1 = open_files(spltd_str[i]);
        i++;
    }
    return (f1);
}
