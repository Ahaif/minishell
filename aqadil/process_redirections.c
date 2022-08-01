/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_redirections.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqadil <aqadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 16:05:53 by ahaifoul          #+#    #+#             */
/*   Updated: 2022/02/23 02:47:58 by aqadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*open_other_files(char *str)
{
	char	**spltd_str;
	int		i;
	char	*temp;
	int		f1;

	i = 1;
	spltd_str = ft_split(str, ' ');
	while (spltd_str[i])
	{
		temp = ft_strtrim(spltd_str[i], " ");
		f1 = open(temp, O_RDWR, 0644);
		if (f1 < 0)
			perror("No  directory");
		free(temp);
		i++;
	}
	return (ft_strtrim(spltd_str[0], " "));
}

int	open_normal_file(char *spltd_str, char c, char *append)
{
	char	*temp;
	int		flag;
	int		f1;

	flag = 0;
	temp = ft_strtrim(spltd_str, " ");
	if (cmd_contain(temp, ' '))
	{
		temp = open_other_files(spltd_str);
		flag++;
	}
	if (append)
		f1 = only_open_append(temp);
	else
		f1 = only_open(temp, c);
	free(temp);
	return (f1);
}

int	escape_cmd_open_file(char *str)
{
	char	**spltd_str;
	int		i;
	int		f1;
	int		flag;

	flag = 0;
	i = 0;
	spltd_str = ft_split(str, '>');
	while (spltd_str[i])
	{
		if (spltd_str[i + 1] != NULL)
			f1 = open_normal_file(spltd_str[i + 1], '>', NULL);
		else
			f1 = open_normal_file(spltd_str[i], '>', NULL);
		i++;
	}
	free(spltd_str);
	return (f1);
}

char	*get_cmmd(char *str)
{
	char	*cmd;
	int		i;

	i = 0;
	if (str_str(str, "<<"))
		cmd = get_cmd_heredoc(str);
	else if (cmd_contain(str, '>') && (!cmd_contain(str, '<'))
		&& (!str_str(str, ">>") && (!str_str(str, "<<"))))
		cmd = get_cmd_io(str, '>');
	else if (cmd_contain(str, '<') && (!cmd_contain(str, '>')
			&& (!str_str(str, ">>") && (!str_str(str, "<<")))))
		cmd = get_cmd_io(str, '<');
	else if (cmd_contain(str, '<') && (cmd_contain(str, '>')
			&& (!str_str(str, ">>") && (!str_str(str, "<<")))))
		cmd = get_cmd_io(str, '<');
	else if ((str_str(str, ">>") && !cmd_contain(str, '<')
			&& !not_contain(str, '>') && !str_str(str, "<<")))
		cmd = get_cmd_app(str);
	else if ((str_str(str, ">>") && (!str_str(str, "<<")
				&& (cmd_contain(str, '<') || not_contain(str, '>')))))
		cmd = get_cmd_app(str);
	return (ft_strtrim(cmd, " "));
}

void	process_redirections(char **parsed_pipe
		, int i, int old_pipe, int *pipe_fd)
{
	int		f1;
	char	*cmd;

	f1 = open_files(parsed_pipe[i]);
	read_from_pipe(parsed_pipe[i], old_pipe);
	if (cmd_contain(parsed_pipe[i], '>') || str_str(parsed_pipe[i], ">>"))
	{
		dup2(f1, STD_OUTPUT);
		close(f1);
	}
	else if (parsed_pipe[i + 1] != NULL && !not_contain(parsed_pipe[i], '>')
		&& !str_str(parsed_pipe[i], ">>"))
		dup2(pipe_fd[1], STD_OUTPUT);
	else if (parsed_pipe[i + 1] == NULL && !cmd_contain(parsed_pipe[i], '>')
		&& !str_str(parsed_pipe[i], ">>"))
		dup2(1, STD_OUTPUT);
	close(pipe_fd[1]);
	cmd = get_cmmd(parsed_pipe[i]);
	execute_cmd(cmd);
}	
