/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqadil <aqadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 20:25:21 by aqadil            #+#    #+#             */
/*   Updated: 2022/01/19 16:19:36 by aqadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int cmd_contain(char *str, char c)
{
    while (*str)
    {
        if (*str == c)
            return (1);
        str++;
    }
    return (0);
}

void handle_multiple_cmd(char *str, t_cmd *cmd)
{
    char **cmd_split;
    int i = 0;

    cmd_split = ft_split(str, ';');
    while (cmd_split[i])
    {
        execute_single_cmd_handler(cmd_split[i]);
        i++;
    }
}

void handle_absolute_path(t_cmd *cmd)
{
    pid_t pid;

    pid = fork();
    if (pid == 0)
    {
        if (execv(cmd->cmd, cmd->args))
            printf("An Error Has ocurred\n");
        exit(0);
    }
}

void parser_and_execute(t_cmd *cmd)
{
    char *str;
    char **args;

    //perror("PASS\n");
    // write(1, "wqq\n", 4);
    str = readline("-> minishell : ");
    // str = "wc < test.txt < test1.txt > test2.txt >> test3.txt";
    // str = parse_line(str);   // you sould handle back slash
    if (str[0] == '\0')
        return;
    add_history(str);
    if (cmd_contain(str, ';'))
        handle_multiple_cmd(str, cmd); // hna ila kano cmd bzaf fihom ";"
    /*else if (str_str(str, "<<"))
        handle_heredoc(str);*/
    else if ((not_contain(str, '>') || cmd_contain(str, '<') || str_str(str, ">>") || str_str(str, "<<")) && (!cmd_contain(str, '|')))
    {
        handlle_redirections(str);
    }
    else if (cmd_contain(str, '|'))
        handlle_pipe(str);
    else
    {
        args = ft_split(str, ' ');
        cmd->cmd = args[0];
        cmd->args = &args[0];
        if (cmd_contain(cmd->cmd, '/'))
            handle_absolute_path(cmd); // hna l absolut path
        else
            execute_single_cmd_handler(str); // hna ghir command wehda
    }
}