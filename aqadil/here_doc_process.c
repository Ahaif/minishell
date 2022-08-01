/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_process.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqadil <aqadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 16:00:42 by ahaifoul          #+#    #+#             */
/*   Updated: 2022/02/23 03:15:02 by aqadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_cmd_heredoc(char *str)
{
	int		i;
	char	**spltd_str;
	char	*cmd;

	i = 0;
	spltd_str = ft_split22(str, "<<");
	if (cmd_contain(spltd_str[0], '<')
		|| cmd_contain(spltd_str[0], '>') || str_str(spltd_str[0], ">>"))
		cmd = get_cmmd(spltd_str[0]);
	else
		cmd = spltd_str[0];
	free(spltd_str);
	return (cmd);
}

int	*get_heredoc_content(char *str)
{
	char	**spltd_str;
	int		i;
	int		j;
	int		*here_doc;
	int		count;

	i = 0;
	j = 0;
	count = 0;
	spltd_str = ft_split(str, '|');
	count = get_count_hd(str);
	here_doc = malloc(sizeof(int) * count + 1);
	while (spltd_str[i])
	{
		if (str_str(spltd_str[i], "<<"))
		{
			here_doc[j] = open_heredoc(spltd_str[i]);
			j++;
		}
		i++;
	}
	return (here_doc);
}

int	open_files_heredoc(char *str)
{
	int		f1;
	char	**spltd_str;
	int		i;

	i = 0;
	spltd_str = ft_split22(str, "<<");
	while (spltd_str[i])
	{
		if (not_contain(spltd_str[i], '>')
			|| str_str(spltd_str[i], ">>") || not_contain(spltd_str[i], '<'))
			f1 = open_files(spltd_str[i]);
		i++;
	}
	return (f1);
}

void	here_doc_process(t_var *var, int i)
{
	int		f2;
	char	*cmd;

	f2 = open_files_heredoc(var->parsed_pipe[i]);
	if (not_contain(var->parsed_pipe[i], '>')
		|| str_str(var->parsed_pipe[i], ">>"))
	{
		dup2(f2, STD_OUTPUT);
		close(f2);
	}
	else if (var->parsed_pipe[i + 1] != NULL
		&& !not_contain(var->parsed_pipe[i], '>')
		&& !str_str(var->parsed_pipe[i], ">>"))
	{
		dup2(var->pipe_fd[1], STD_OUTPUT);
		close(var->pipe_fd[1]);
	}
	else if (var->parsed_pipe[i + 1] == NULL
		&& !not_contain(var->parsed_pipe[i], '>')
		&& !str_str(var->parsed_pipe[i], ">>"))
		dup2(1, STD_OUTPUT);
	dup2(var->here_doc[var->heredoc_index], STD_INPUT);
	close(var->here_doc[var->heredoc_index]);
	cmd = get_cmd_heredoc(var->parsed_pipe[i]);
	execute_cmd(cmd);
}

int	get_count_hd(char *str)
{
	char	**spltd_str;
	int		i;
	int		count;

	i = 0;
	count = 0;
	spltd_str = ft_split(str, '|');
	while (spltd_str[i])
	{
		if (str_str(spltd_str[i], "<<"))
			count++;
		i++;
	}
	return (count);
}
