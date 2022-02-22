/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle.redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaifoul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 15:36:07 by ahaifoul          #+#    #+#             */
/*   Updated: 2022/02/05 16:10:27 by ahaifoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *get_special_cmd(char *str)
{
    char **temp;
    char **temp1;
    char *cmd;
    char **temp2;

    if (cmd_contain(str, '>'))
        temp = ft_split(str, '>');
    else
        temp = ft_split(str, '<');

    if (cmd_contain(temp[0], '<'))
    {
        temp1 = ft_split(temp[0], '<');
        cmd = temp1[0];
        return (ft_strtrim(cmd, " "));
    }
    else if (cmd_contain(temp[0], '>'))
    {
        temp1 = ft_split(temp[0], '>');
        cmd = ft_strdup(temp1[0]);
    }
    else
        cmd = ft_strdup(temp[0]);
    //free(temp);
    //free(temp1);
    return (ft_strtrim(cmd, " "));
}

int escape_cmd_open_file(char *str)
{
    char **spltd_str;
    int i;
    int f1;

    i = 0;
    spltd_str = ft_split(str, '>');
    while (spltd_str[i])
    {
        if (spltd_str[i + 1] != NULL)
            f1 = open(ft_strtrim(spltd_str[i + 1], " "), O_CREAT | O_RDWR | O_TRUNC, 0644);
        else
            f1 = open(ft_strtrim(spltd_str[i], " "), O_CREAT | O_RDWR | O_TRUNC, 0644);
        if (f1 < 0)
            handle_fd_error(f1);
        i++;
    }
    free(spltd_str);
    return (f1);
}
//f1 = open_file_rt(splt_str);

int open_file_rt(char **splt_str)
{
    int i;
    int f1;

    i = 0;
    while (splt_str[i])
    {
        if (i == 0)
        {
            f1 = open(ft_strtrim(splt_str[i], " "), O_RDWR, 0644);
            if (f1 < 0)
                handle_fd_error(f1);
        }
        else
        {
            f1 = open(ft_strtrim(splt_str[i], " "), O_CREAT | O_RDWR | O_TRUNC, 0644);
            if (f1 < 0)
                handle_fd_error(f1);
        }
        i++;
    }
    return (f1);
}

int open_file_greater(char *str, int index)
{
    char **splt_str;
    int i;
    int f1;

    i = 0;
    splt_str = ft_split(str, '>');
    if (index == 0)
        f1 = escape_cmd_open_file(str);
    else
        f1 = open_file_rt(splt_str);
    return (f1);
}

void open_file_less(char *str, int index)
{
    int f1;

    if (index == 0)
        f1 = 0;
    else
    {
        f1 = open(ft_strtrim(str, " "), O_RDWR, 0644);
        if (f1 < 0)
            handle_fd_error(f1);
        close(f1);
    }
}

char *open_other_files(char *str)
{
    char **spltd_str;
    int i;
    char *temp;
    int f1;

    i = 1;
    spltd_str = ft_split(str, ' ');
    while (spltd_str[i])
    {
        temp = ft_strtrim(spltd_str[i], " ");
        f1 = open(temp, O_RDWR, 0644);
        if (f1 < 0)
            perror("No such file or directory");
        free(temp);
        i++;
    }
    return (ft_strtrim(spltd_str[0], " "));
}

// void check_str_nw(char *str, char c, int f1)
// {
//     int i;
//     char **spltd_str;
//     char *cmd;
//     int pid;

//     cmd = handle_wp(str, c);

//     pid = fork();
//     if (pid == 0)
//     {
//         if (c == '<')
//             dup2(get_fd_input(str), STD_INPUT);
//         dup2(f1, STD_OUTPUT);

//         check_acces(cmd);
//         execute_cmd(cmd);
//     }
//     else
//         waitpid(-1, NULL, 0);
// }

// char *handle_wp(char *str, char c)
// {
//     char **spltd_str;
//     int i = 0;
//     char *temp;
//     char *line = NULL;
//     char **temp1;

//     spltd_str = ft_split(str, c);
//     while (spltd_str[i])
//     {
//         temp = ft_strtrim(spltd_str[i], " ");
//         if (cmd_contain(temp, ' '))
//         {
//             temp1 = ft_split(spltd_str[i], ' ');

//             line = ft_strtrim(temp1[1], " ");
//             return (line);
//         }
//         free(temp);
//         i++;
//     }
//     return (NULL);
// }

int truncat_mod_fd(char *str) // escape cmd and send Output fd
{
    char **spltd_str;
    char *temp;
    int i;
    int f1;
    int flag;

    flag = 0;
    i = 1;
    spltd_str = ft_split(str, '>');
    while (spltd_str[i])
    {
        temp = ft_strtrim(spltd_str[i], " ");
        if (cmd_contain(spltd_str[i], ' '))
        {
            temp = open_other_files(spltd_str[i]);
            flag++;
        }
        f1 = only_open(temp, '>');
        i++;
    }
    // if (flag != 0)
    // {
    //     check_str_nw(str, '>', f1); // only  rdr output // execute and exit
    //     f1 = 0;
    // }
    return (f1);
}
int only_rd_fd(char *str)
{
    char **spltd_str;
    char *temp;
    int i;
    int f1;
    int flag;

    i = 1;
    flag = 0;
    spltd_str = ft_split(str, '<');
    while (spltd_str[i])
    {
        temp = ft_strtrim(spltd_str[i], " ");
        if (cmd_contain(spltd_str[i], ' '))
        {
            temp = open_other_files(spltd_str[i]);
            flag++;
        }
        f1 = only_open(temp, '<');
        i++;
    }
    // if (flag != 0)
    // {
    //     check_str_nw(str, '>', f1); // only  rdr output // execute and exit
    //     f1 = 0;
    // }
    return (1);
}

int input_output_redirect(char *str)
{
    char **spltd_str;
    int i;
    int f1;

    spltd_str = ft_split(str, '<');
    i = 0;
    while (spltd_str[i])
    {
        if (cmd_contain(spltd_str[i], '>'))
            f1 = open_file_greater(spltd_str[i], i);
        else
            open_file_less(spltd_str[i], i);
        i++;
    }
    return (f1);
}

int only_append_fd(char *str)
{
    char **spltd_str;
    int i;
    int f1;

    i = 1;
    spltd_str = ft_split22(str, ">>");
    while (spltd_str[i])
    {
        if (spltd_str[i + 1] != NULL)
            f1 = open(ft_strtrim(spltd_str[i + 1], " "), O_CREAT | O_RDWR | O_APPEND, 0644);
        else
            f1 = open(ft_strtrim(spltd_str[i], " "), O_CREAT | O_RDWR | O_APPEND, 0644);
        if (f1 < 0)
            handle_fd_error(f1);
        i++;
    }
    return (f1);
}

int open_files(char *str)
{
    int i;
    int f1;
    char *temp;
    char **spltd_str;

    if (cmd_contain(str, '>') && !cmd_contain(str, '<') && !str_str(str, ">>") && !str_str(str, "<<"))
        f1 = truncat_mod_fd(str);
    else if (cmd_contain(str, '<') && !not_contain(str, '>') && !str_str(str, ">>") && !str_str(str, "<<"))
        f1 = only_rd_fd(str);
    else if (cmd_contain(str, '<') && not_contain(str, '>') && !str_str(str, ">>") && !str_str(str, "<<"))
        f1 = input_output_redirect(str);
    else if ((str_str(str, ">>") && !not_contain(str, '<') && !not_contain(str, '>') && !str_str(str, "<<")))
        f1 = only_append_fd(str);
    else if (str_str(str, ">>") && (!str_str(str, "<<") && (cmd_contain(str, '<') || cmd_contain(str, '>'))))
        f1 = open_files_appe(str);
    return (f1);
}

char *get_cmd_app(char *str)
{
    char **spltd_str;
    char *cmd;

    spltd_str = ft_split22(str, ">>");
    if (cmd_contain(spltd_str[0], '>') || cmd_contain(spltd_str[0], '<'))
        cmd = get_special_cmd(spltd_str[0]);
    else
        cmd = spltd_str[0];
    return (cmd);
}

char *get_cmd_io(char *str, char c)
{
    char **spltd_str;
    char *cmd;

    if (c == '>')
    {
        spltd_str = ft_split(str, '>');
        cmd = spltd_str[0];
    }
    else if (c == '<')
    {
        spltd_str = ft_split(str, '<');
        if (cmd_contain(spltd_str[0], '>'))
            cmd = get_special_cmd(spltd_str[0]);
        else
            cmd = spltd_str[0];
    }
    free(spltd_str);
    return (cmd);
}

char *get_cmmd(char *str)
{
    char *cmd;
    int i;

    i = 0;
    if (str_str(str, "<<"))
        cmd = get_cmd_heredoc(str);
    else if (cmd_contain(str, '>') && (!cmd_contain(str, '<')) && (!str_str(str, ">>") && (!str_str(str, "<<"))))
        cmd = get_cmd_io(str, '>');
    else if (cmd_contain(str, '<') && (!cmd_contain(str, '>') && (!str_str(str, ">>") && (!str_str(str, "<<")))))
        cmd = get_cmd_io(str, '<');
    else if (cmd_contain(str, '<') && (cmd_contain(str, '>') && (!str_str(str, ">>") && (!str_str(str, "<<")))))
        cmd = get_cmd_io(str, '<');
    else if ((str_str(str, ">>") && !cmd_contain(str, '<') && !not_contain(str, '>') && !str_str(str, "<<")))
        cmd = get_cmd_app(str);
    else if ((str_str(str, ">>") && (!str_str(str, "<<") && (cmd_contain(str, '<') || not_contain(str, '>')))))
        cmd = get_cmd_app(str);
    return (ft_strtrim(cmd, " "));
}

int not_contain(char *str, char c)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] != c && str[i + 1] == c && str[i + 2] != c)
            return (1);
        i++;
    }
    return (0);
}

//redirec_child_process(str, f2, f1)
void redirec_child_process(char *str, int f2, int f1)
{
    char *cmd;

    if (str_str(str, "<<"))
        cmd = get_cmd_heredoc(str);
    else
        cmd = get_cmmd(str);

    if (str_str(str, "<<"))
    {
        dup2(f2, STD_INPUT);
        close(f2);
    }
    if (cmd_contain(str, '<'))
        dup2(f2, STD_INPUT);
    dup2(f1, STD_OUTPUT);

    close(f2);
    // close(f1);
    check_acces(cmd);
    execute_cmd(cmd);
}

void handlle_redirections(char *str)
{
    int f1;
    int pid;
    int f2;

    if (str_str(str, "<<"))
    {
        f2 = open_heredoc(str);
        f1 = open_files_heredoc(str);
    }
    else
    {
        f1 = open_files(str);
        if (cmd_contain(str, '<'))
            f2 = get_fd_input(str);
    }
    pid = fork();
    if (pid == -1)
        return (perror("Fork error"));
    if (pid == 0)
        redirec_child_process(str, f2, f1);
    else
        wait(NULL);
}
