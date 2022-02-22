/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaifoul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 16:56:16 by ahaifoul          #+#    #+#             */
/*   Updated: 2022/02/10 16:56:31 by ahaifoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void redirect_input(char **parsed_pipe, int i, int *fd_pp)
{
    int fd_in1;

    fd_in1 = get_fd_input(parsed_pipe[i]);
    dup2(fd_in1, STD_INPUT);
    // if (parsed_pipe[i + 1] != NULL)
    //     dup2((fd_pp[1]), STD_OUTPUT);

    execute_cmd(get_cmd(parsed_pipe[i]));
    exit(0);
}

//void parent_process