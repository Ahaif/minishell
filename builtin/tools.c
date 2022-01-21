/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqadil <aqadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 00:43:42 by aqadil            #+#    #+#             */
/*   Updated: 2022/01/19 17:44:38 by aqadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../aqadil/minishell.h"

int ft_strcmp(const char *s1, const char *s2)
{
    int i;

    i = 0;
    while (s1[i] || s1[i])
    {
        if(s1[i] != s2[i])
            return (1);
        i++;
    }
    return (0);
}

char    *ft_solution(char *line, int pos)
{
    char *cmd;
    int i;

    i = pos;
    while (line[i])
        i++;
    cmd = malloc(i + 1);
    i = 0;
    while (line[pos])
    {
        cmd[i] = line[pos];
        i++;
        pos++;
    }
    return (cmd);
}