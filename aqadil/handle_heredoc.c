/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqadil <aqadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 11:23:58 by ahaifoul          #+#    #+#             */
/*   Updated: 2022/02/23 01:45:56 by aqadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_cmd_heredoc(char *str, int fd_heredoc)
{
	char	*cmd;
	int		f2;
	int		pid;

	cmd = get_cmd_heredoc(str);
	dup2(fd_heredoc, STD_INPUT);
	close(fd_heredoc);
	f2 = open_files_heredoc(str);
	if (not_contain(str, '>') || str_str(str, ">>"))
	{
		dup2(f2, STD_OUTPUT);
		close(f2);
	}
	pid = fork();
	if (pid == -1)
		return (perror("Fork error"));
	if (pid == 0)
		execute_cmd(cmd);
	else
		waitpid(-1, 0, 0);
	exit(0);
}

char	*read_line(char **spltd_str, char *del)
{
	char	*line;
	int		i;
	char	*temp1;

	i = 1;
	while (spltd_str[i])
	{
		line = readline("-> heredoc: ");
		while (line)
		{
			if (strcmp(line, del) == 0)
				break ;
			if (spltd_str[i + 1] == NULL)
				temp1 = str_join_heredoc(temp1, line);
			line = readline("-> heredoc: ");
		}
		i++;
	}
	return (temp1);
}

void	var_t_help(t_role *var)
{
	var->i = 1;
}

int	open_heredoc(char *str_heredoc)
{
	t_role	var;

	var_t_help(&var);
	var.spltd_str = ft_split22(str_heredoc, "<<");
	pipe(var.fd_pipe);
	while (var.spltd_str[var.i])
	{
		var.del = get_delimetr(var.spltd_str[var.i]);
		var.line = readline("-> heredoc: ");
		while (var.line)
		{
			if (strcmp(var.line, var.del) == 0)
				break ;
			if (var.spltd_str[var.i + 1] == NULL)
				var.temp1 = str_join_heredoc(var.temp1, var.line);
			var.line = readline("-> heredoc: ");
		}
		var.i++;
	}
	var.temp1 = ft_strjoin2_2(var.temp1, "\n");
	write(var.fd_pipe[1], var.temp1, str_len(var.temp1));
	close(var.fd_pipe[1]);
	return (var.fd_pipe[0]);
}
