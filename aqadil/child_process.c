/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqadil <aqadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 16:24:51 by ahaifoul          #+#    #+#             */
/*   Updated: 2022/02/23 03:15:33 by aqadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	read_from_pipe(char *parsed_pipe, int old_pipe)
{
	int	f2;

	if (!not_contain(parsed_pipe, '<'))
	{
		dup2(old_pipe, STD_INPUT);
		if (old_pipe != 0)
			close(old_pipe);
	}
	else if (cmd_contain(parsed_pipe, '<'))
	{
		f2 = get_fd_input(parsed_pipe);
		dup2(f2, STD_INPUT);
		close(f2);
	}
}

void	child_process(t_var *var, int i)
{
	close(var->pipe_fd[0]);
	if (str_str(var->parsed_pipe[i], "<<"))
		here_doc_process(var, i);
	check_acces(var->parsed_pipe[i]);
	if ((not_contain(var->parsed_pipe[i], '<')
			|| not_contain(var->parsed_pipe[i], '>')
			|| str_str(var->parsed_pipe[i], ">>"))
		&& !str_str(var->parsed_pipe[i], "<<"))
		process_redirections(var->parsed_pipe, i, var->old_pipe, var->pipe_fd);
	else
		process_pipes(var->parsed_pipe, i, var->pipe_fd, var->old_pipe);
}

char	*get_cmd(char *str)
{
	int		i;
	char	*temp;

	temp = NULL;
	i = 0;
	if (cmd_contain(str, '<'))
		temp = splt_str(str, '<', NULL);
	else if ((cmd_contain(str, '>')) && !str_str(str, ">>")
		&& !cmd_contain(str, '<'))
		temp = splt_str(str, '<', NULL);
	else if (str_str(str, ">>"))
		temp = splt_str(str, 'n', ">>");
	return (temp);
}

char	*splt_str(char *str, char c, char *red)
{
	char	**spltd_str;
	char	*temp;

	temp = NULL;
	spltd_str = NULL;
	if (red)
	{
		spltd_str = ft_split22(str, red);
		temp = ft_strtrim(spltd_str[0], " ");
	}
	else
	{
		spltd_str = ft_split(str, c);
		temp = ft_strtrim(spltd_str[0], " ");
	}
	return (temp);
}

int	get_infile_fd(char *str)
{
	char	**spltd_str;
	char	*temp;
	int		f1;

	f1 = 0;
	if (cmd_contain(str, '<'))
	{
		spltd_str = ft_split(str, '<');
		temp = ft_strtrim(spltd_str[1], " ");
		f1 = open(temp, O_RDWR, 0644);
		if (f1 < 0)
			perror("fd Error");
	}
	else if (cmd_contain(str, '>') && (!str_str(str, ">>")))
	{
		spltd_str = ft_split(str, '>');
		temp = ft_strtrim(spltd_str[1], " ");
		f1 = open(temp, O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (f1 < 0)
			perror("fd Error");
	}
	else if (str_str(str, ">>"))
		f1 = open_append_mode(str);
	return (f1);
}
