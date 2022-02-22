/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaifoul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 11:38:01 by ahaifoul          #+#    #+#             */
/*   Updated: 2022/02/07 11:38:59 by ahaifoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int open_file_gr(char *str, int index)
{
    char **temp;
    int i;
    int f1;
    int f2;

    i = 0;
    temp = ft_split(str, '>');
    while (temp[i])
    {
        if (index == 0)
        {
            f1 = open(ft_strtrim(temp[0], " "), O_CREAT | O_RDWR | O_APPEND, 0644);
            if (f1 < 0)
                handle_fd_error(f1);
        }
        else
            f2 = only_open(temp[i], '>');
        i++;
    }
    return (f1);
}

int special_open_for_append(char *str)
{
    char **spltd_str;
    int i;
    int f1;

    i = 0;
    spltd_str = ft_split(str, '>');
    while (spltd_str[i])
    {
        if (i == 0)
            f1 = only_open_append(spltd_str[i]);
        else
            f1 = only_open(spltd_str[i], '>');
        i++;
    }
    return (f1);
}

int append_to_first_file(char *str)
{
    char **spltd_str;
    int i;
    int f1;
    int f2;

    i = 0;
    spltd_str = ft_split(str, '<');
    while (spltd_str[i])
    {
        if (cmd_contain(spltd_str[i], '>'))
            f1 = special_open_for_append(spltd_str[i]); //f1 = open_files(spltd_str[i]); // file to append
        else
        {
            if (i == 0)
                f2 = only_open_append(spltd_str[0]); //close (f2)
            else
                f2 = only_open(spltd_str[i], '<'); //close(f2);
        }
        i++;
    }
    return (f1);
}

int output_redirect(char *str)
{
    char **spltd_str;
    int i;
    int f1;
    int f2;

    i = 0;
    spltd_str = ft_split(str, '>');
    while (spltd_str[i])
    {
        if (i == 0)
        {
            f2 = open(ft_strtrim(spltd_str[i], " "), O_CREAT | O_RDWR, 0644);
            if (f2 < 0)
                handle_fd_error(f2);
        }
        else
            f1 = only_open(spltd_str[i], '>');
        i++;
    }
    return (f1);
}

int input_redirect(char *str)
{
    char **spltd_str;
    int i;
    int f1;
    int f2;

    i = 0;
    spltd_str = ft_split(str, '<');
    i = 0;
    while (spltd_str[i])
    {
        if (i == 0)
            f1 = only_open_append(spltd_str[i]);
        else
            f2 = only_open(spltd_str[i], '<');
        i++;
    }
    return (f1);
}

int open_files_gre(char *str)
{
    int f2;
    int f1;

    if (cmd_contain(str, '>') && (!cmd_contain(str, '<')))
        f1 = output_redirect(str);
    else if (cmd_contain(str, '<') && (!cmd_contain(str, '>')))
        f1 = input_redirect(str);
    return (f1);
}

int only_open(char *str, char c)
{
    int f1;

    if (c == '<')
    {
        f1 = open(ft_strtrim(str, " "), O_RDWR, 0644);
        if (f1 < 0)
            handle_fd_error(f1);
    }
    else if (c == '>')
    {
        f1 = open(ft_strtrim(str, " "), O_CREAT | O_RDWR | O_TRUNC, 0644);
        if (f1 < 0)
            handle_fd_error(f1);
    }
    free(str);
    return (f1);
}

int only_open_append(char *str)
{
    int f1;

    f1 = open(ft_strtrim(str, " "), O_CREAT | O_RDWR | O_APPEND, 0644);
    if (f1 < 0)
        handle_fd_error(f1);
    return (f1);
}

//f1 = append_with_redirect(spltd_str, i);

int append_with_redirect(char **spltd_str, int i)
{
    int f1;

    if (not_contain(spltd_str[i], '>') && not_contain(spltd_str[i], '<')) // and instead of or
        f1 = append_to_first_file(spltd_str[i]);
    else
        f1 = open_files_gre(spltd_str[i]);

    return (f1);
}

int open_files_appe(char *str)
{
    int i;
    char **spltd_str;
    int f1;

    spltd_str = ft_split22(str, ">>");
    i = 0;
    while (spltd_str[i])
    {
        if (i == 0)
        {
            if (not_contain(spltd_str[i], '>') || not_contain(spltd_str[i], '<'))
                f1 = open_files(spltd_str[i]);
        }
        else
        {
            if (!cmd_contain(spltd_str[i], '>') && (!cmd_contain(spltd_str[i], '<')))
                f1 = only_open_append(spltd_str[i]);
            else
                f1 = append_with_redirect(spltd_str, i);
        }
        i++;
    }
    return (f1);
}
