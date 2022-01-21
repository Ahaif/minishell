/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqadil <aqadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 00:38:18 by aqadil            #+#    #+#             */
/*   Updated: 2022/01/19 01:37:09 by aqadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../aqadil/minishell.h"

void    cd(char *path)
{
    if (path == NULL)
    {
        if (chdir("/"))
            printf("cd: no such file or directory: %s\n", path);
    }
    else
    {

        if (access(path, R_OK))
            printf("cd: permission denied: %s\n", path);
        else
        {
            if (chdir(path))
                printf("cd: no such file or directory: %s\n", path);
        }
    }
}
