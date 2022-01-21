/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqadil <aqadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 00:21:53 by aqadil            #+#    #+#             */
/*   Updated: 2022/01/19 17:58:26 by aqadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../aqadil/minishell.h"

char *double_quots_check(char *str)
{
    char    *cmd;
    
    if ((str[0] == '\"' && str[ft_strlen(str) - 3] == '\"'))
        cmd = ft_strtrim(str, "\"");
    else if ((str[0] == '\'' && str[ft_strlen(str) - 1] == '\''))
        cmd = ft_strtrim(str, "\'");
    else
        cmd = str;
    return (cmd);
}


void    handle_echo(char *str)
{
    int i;

    i = 0;
    str = double_quots_check(str);
    str = ft_strjoin(str, " \n");
    while (str[i])
    {
        if (str[i] == '\\')
        {
            write(1, &str[i], 1);
            i++;
        }
        else
            write(1, &str[i], 1);
        i++;
    }
}

int check_valid_echo(char *str)
{
    int checker;
    int doubleQ;
    int singleQ;
    int i;

    i = 0;
    checker = 1;
    doubleQ = 0;
    singleQ = 0;
    // printf("%c", str[0]);
    // exit(1);
    if (str[0] != str[ft_strlen(str) - 1])
        return (0);
    while (str[i])
    {
        if (str[0] == '\'' && str[i] == '\'' && str[i - 1] != '\\')
            singleQ++;
        else if (str[0] == '\"' && str[i] == '\"' && str[i - 1] != '\\')
            doubleQ++;
        i++;
    }
    if (doubleQ % 2 != 0 && doubleQ != 0)
    {
        return (0);
    }
    if (singleQ % 2 != 0 && singleQ != 0)
        return (0);
    return (1);
}

char    *remove_echo_and_space(char *line)
{
    char **result;
    char    *args;
    int i;
    
    i = 0;
    result = ft_split(line, ' ');
    args = result[1];
    while (result[i])
    {
        if (i > 0)
        {
            args = ft_strjoin(args, " ");
            args = ft_strjoin(args, result[i]);
        }
        i++;
    }
    return (args);
}

char    *handle_line(char *line)
{
    int i;
    char *cmd;

    i = 0;
    while (line[i])
    {
        if (line[i] == '\'' || line[i] == '\"')
            break;
        i++;
    }
    if (i == ft_strlen(line))
    {
        return (remove_echo_and_space(line));
    }
    cmd = ft_solution(line, i);
    return (cmd);
}

void    echo(char *arg)
{
    char *str;
    int checker;

    str = handle_line(arg);
    printf("|%s|\n", str);
    exit(1);
    checker = check_valid_echo(arg);
    if (checker == 1)
        handle_echo(arg);
    else
        write(1, "echo : error has ocurred\n", 26);
}