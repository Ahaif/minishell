/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaifoul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 10:06:04 by ahaifoul          #+#    #+#             */
/*   Updated: 2022/01/31 10:06:07 by ahaifoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int str_len(char const *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char *op_strjoin(char const *s1, char const *s2)
{
	char *new;
	int i;
	int k;

	if (s1 && s2)
	{
		k = 0;
		i = 0;
		new = (char *)malloc(sizeof(char) * ((str_len(s1) + str_len(s2)) + 2));
		if (new == 0)
			return (0);
		while (s1[i])
		{
			new[i] = s1[i];
			i++;
		}
		new[i++] = '/';
		k = 0;
		while (s2[k])
			new[i++] = s2[k++];
		new[i] = '\0';
		return (new);
	}
	return (0);
}

int *check_str(char *str)
{
	int *here_doc;

	if (str_str(str, "<<"))
		here_doc = get_heredoc_content(str);
	return (here_doc);
}

void check_acces(char *str)
{

	if (check_access(str))
	{
		perror("command not found: ");
		exit(0); ///handlle cmd not found
	}
}
void handle_fd_error(int f1)
{
	if (f1 < 0)
	{
		perror("fg error");
		exit(0);
	}
}

int get_fd_input(char *str)
{
	int i;
	int f1;
	char **spltd_str;
	char **temp;

	i = 0;
	spltd_str = ft_split(str, '<');
	while (spltd_str[i])
	{
		if (spltd_str[i + 1] == NULL)
		{
			if (cmd_contain(spltd_str[i], '>') || str_str(spltd_str[i], ">>"))
			{

				temp = ft_split(spltd_str[i], '>');
				f1 = open(ft_strtrim(temp[0], " "), O_RDWR, 0644);
			}
			else
				f1 = open(ft_strtrim(spltd_str[i], " "), O_RDWR, 0644);
			if (f1 < 0)
				handle_fd_error(f1);
		}
		i++;
	}
	return (f1);
}

void execute_cmd_without_redirect(char **parsed_pipe, int index, int fd_old_input, int fd_heredoc)
{
	int f2;
	char *cmd;
	int f1;

	//dup2(fd_pipe, STD_INPUT);
	// close(*fd_pp[0]);
	if (((cmd_contain(parsed_pipe[index], '<') || not_contain(parsed_pipe[index], '>') || str_str(parsed_pipe[index], ">>"))) && !str_str(parsed_pipe[index], "<<"))
	{
		cmd = get_cmmd(parsed_pipe[index]);

		// if (!not_contain(parsed_pipe[index], '<'))
		// {
		// 	dup2(fd_old_input, STD_INPUT);
		// 	close(fd_old_input);
		// }
		// else if (cmd_contain(parsed_pipe[index], '<')) // recheck this condition
		// {
		// 	f2 = get_fd_input(parsed_pipe[index]);
		// 	dup2(f2, STD_INPUT);
		// 	close(f2);
		// }
		// // if (parsed_pipe[index + 1] != NULL && !not_contain(parsed_pipe[index], '>') && !str_str(parsed_pipe[index], ">>"))
		// // 	dup2(*fd_pp[1], STD_OUTPUT);
		// else if (cmd_contain(parsed_pipe[index], '>') || str_str(parsed_pipe[index], ">>"))
		// {
		// 	f1 = open_files(parsed_pipe[index]);
		// 	dup2(f1, STD_OUTPUT);
		// 	close(f1);
		// }
		// dup2(get_infile_fd(parsed_pipe[index]), STD_OUTPUT);
	}
	// else if (str_str(parsed_pipe[index], "<<"))
	// {
	// 	cmd = get_cmd_heredoc(parsed_pipe[index]);
	// 	dup2(fd_heredoc, STD_INPUT);
	// 	close(fd_old_input);

	// 	if (parsed_pipe[index + 1] != NULL && !not_contain(parsed_pipe[index], '>') && !str_str(parsed_pipe[index], ">>"))
	// 		dup2(*fd_pp[1], STD_OUTPUT);
	// 	else
	// 		dup2(open_files_heredoc(parsed_pipe[index]), STD_OUTPUT);
	// }
	// else
	// 	dup2(fd_old_input, STD_INPUT);

	execute_cmd(cmd);
}