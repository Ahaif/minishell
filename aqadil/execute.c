/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqadil <aqadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 20:42:42 by aqadil            #+#    #+#             */
/*   Updated: 2022/01/19 15:53:04 by aqadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    execute(t_cmd *cmd)
{
    char    *path = "/bin/";
    int i = 0;
    char    *c_cmd;

    c_cmd = ft_strjoin(path, cmd->cmd); 
    if (execv(c_cmd, cmd->args))
        printf("Error Has Ocurred\n");
    exit(0);
}

