/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqadil <aqadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 16:01:05 by aqadil            #+#    #+#             */
/*   Updated: 2022/01/19 02:49:45 by aqadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./aqadil/minishell.h"

// gheda ay5esk t9aleb flpath variable 3la command wach kayna

int main(int argc, char **argv)
{
    t_cmd cmd;
    pid_t pid;

    while (1)
    {
        parser_and_execute(&cmd);
        waitpid(-1, 0, 0);
    }
    return (0);
}
