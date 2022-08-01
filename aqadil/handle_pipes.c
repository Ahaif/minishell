/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hand_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaifoul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 13:24:10 by ahaifoul          #+#    #+#             */
/*   Updated: 2022/02/22 21:21:19 by ahaifoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_pipes(char **parsed_pipe, int i, int *pipe_fd, int old_pipe)
{
	if (parsed_pipe[i + 1] != NULL)
		dup2(pipe_fd[1], STD_OUTPUT);
	dup2(old_pipe, STD_INPUT);
	if (old_pipe != 0)
		close(old_pipe);
	close(pipe_fd[1]);
	execute_cmd(parsed_pipe[i]);
}

int	parent_process(t_var var, int i)
{
	int	status;

	status = 0;
	close(var.pipe_fd[1]);
	if (var.old_pipe != 0)
		close(var.old_pipe);
	var.old_pipe = var.pipe_fd[0];
	if (var.parsed_pipe[i + 1] == NULL)
	{
		waitpid(var.pid, &status, 0);
		if (WIFEXITED(status))
			status = WEXITSTATUS(status);
	}
	g_env_var.status = status;
	return (var.old_pipe);
}

void	handle_pipe_init(t_var *var)
{
	var->old_pipe = 0;
	var->heredoc_index = 0;
	var->i = 0;
}

void	handlle_pipe(char *str)
{
	t_var	variable;

	handle_pipe_init(&variable);
	variable.parsed_pipe = pipe_spliter(str);
	if (str_str(str, "<<"))
		variable.here_doc = check_str(str);
	while (variable.parsed_pipe[variable.i])
	{
		pipe(variable.pipe_fd);
		variable.pid = fork();
		if (variable.pid == -1)
			perror("Fork error");
		if (variable.pid == 0)
			child_process(&variable, variable.i);
		else
		{
			variable.old_pipe = parent_process(variable, variable.i);
			if (str_str(variable.parsed_pipe[variable.i], "<<"))
				variable.heredoc_index++;
		}
		variable.i++;
	}
	while (wait(NULL) != -1)
		;
}
