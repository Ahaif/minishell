/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqadil <aqadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 21:30:10 by aqadil            #+#    #+#             */
/*   Updated: 2022/01/19 17:47:46 by aqadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    *path_search(char *cmd)
{
    char    **str;
    char    *env;
    char    *path;
    char    *path_search;
    int i = 0;

    env = getenv("PATH");
    str = ft_split(env, ':');
    while (str[i])
    {
        path = ft_strjoin(str[i], "/");
        path_search = ft_strjoin(path, cmd);
        if (access(path_search, X_OK) == 0)
            return (path);
        i++;
    }
    return (NULL);
}

void    execute_single_cmd_handler(char *line)
{
    char    **args;
    char    *cmd;
    char    *path;
    
    args = ft_split(line, ' ');
    cmd = args[0];
    path = path_search(cmd);
    if (ft_strcmp(cmd, "cd") == 0)
        cd(args[1]);
    else if (ft_strcmp(cmd, "echo") == 0)
    {
        // printf("|%s|\n", line);
        echo(line);
    }
    else if (cmd_contain(line, '/'))
        execute_single_cmd("", cmd, args);
    else
        execute_single_cmd(path, cmd, args);
}

void    execute_single_cmd(char *path, char *cmd, char **args)
{
    pid_t   pid;

    cmd = ft_strjoin(path, cmd);
    pid = fork();
    if (pid == 0)
    {
        if (execve(cmd, args, NULL))
            printf("Error Has Ocurred\n");
        exit(0);
    }
    wait(NULL);
}
