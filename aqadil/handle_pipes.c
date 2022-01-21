/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hand_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaifoul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 13:24:10 by ahaifoul          #+#    #+#             */
/*   Updated: 2022/01/20 18:12:09 by ahaifoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int str_len(char const *str)
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

char **get_path(void)
{

	char *path_from_envp;
	char **spltd_paths;

	path_from_envp = getenv("PATH");
	spltd_paths = ft_split(path_from_envp, ':');
	return (spltd_paths);
}

int check_access(char *str)
{
	char **spltd_paths;
	char **cmd_options;
	char *access_par;
	int i;
	int ret;

	cmd_options = ft_split(str, ' '); // file name should be handled !!
	spltd_paths = get_path();
	i = 0;
	while (spltd_paths[i++])
	{
		access_par = op_strjoin(spltd_paths[i], cmd_options[0]);
		ret = access(access_par, X_OK);
		if (ret == 0)
			return (0);
	}
	return (1);
}

void execute_cmd(char *str)
{
	char **cmd_arg;
	char *execve_param;
	char **spltd_paths;
	int i;

	cmd_arg = ft_split(str, ' '); // file name should be handled !!!
	spltd_paths = get_path();
	while (spltd_paths[i++])
	{
		execve_param = op_strjoin(spltd_paths[i], cmd_arg[0]);
		execve(execve_param, cmd_arg, NULL);
		free(execve_param);
	}
	return (perror("execve error: "));
}

void handlle_pipe(char *str)
{

	char **parsed_pipe;
	int fd[2];
	int pid;
	int fd_in;
	int i;

	i = 0;
	parsed_pipe = ft_split(str, '|');
	/*while (parsed_pipe[i++])
	{
		if (!check_access(parsed_pipe[i]))
			return (perror("command not found: "));
	}*/

	i = 0;
	while (parsed_pipe[i++])
	{
		pipe(fd);
		pid = fork();
		if (pid == 0)
		{
			close(fd[0]);
			dup2(fd_in, STD_INPUT); // change the input to the according old one
			if (parsed_pipe[i + 1] != NULL)
				dup2(fd[1], STD_OUTPUT);
			execute_cmd(parsed_pipe[i]);
		}
		else
		{
			wait(NULL);
			close(fd[1]);
			fd_in = fd[0];
		}
	}
}
