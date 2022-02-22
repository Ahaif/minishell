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
		ret = access(access_par, X_OK | F_OK);
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

	i = 0;
	cmd_arg = ft_split(str, ' '); // file name should be handled !!!
	spltd_paths = get_path();
	while (spltd_paths[i++])
	{
		execve_param = op_strjoin(spltd_paths[i], cmd_arg[0]);
		execve(execve_param, cmd_arg, NULL);
		free(execve_param);
	}
	return (perror("exve error: "));
}

int open_append_mode(char *str)
{
	char **spltd_str;
	char *temp;
	int f1;

	spltd_str = ft_split22(str, ">>");
	temp = ft_strtrim(spltd_str[1], " ");
	f1 = open(temp, O_CREAT | O_RDWR | O_APPEND, 0644);
	if (f1 < 0)
	{
		perror("fd : error");
		exit(0);
	}
	return (f1);
}

int get_infile_fd(char *str)
{
	char **spltd_str;
	char *temp;
	int f1;

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

	return (f1); // free temp and spltd_str
}

char *splt_str(char *str, char c, char *red)
{
	char **spltd_str;
	char *temp;
	int i;

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
char *get_cmd(char *str)
{
	int i;
	char **spltd_str;
	char *temp;

	i = 0;
	if (cmd_contain(str, '<'))
		temp = splt_str(str, '<', NULL);
	else if ((cmd_contain(str, '>')) && !str_str(str, ">>") && !cmd_contain(str, '<'))
		temp = splt_str(str, '<', NULL);
	else if (str_str(str, ">>"))
		temp = splt_str(str, 'n', ">>");
	return (temp);
}

int get_count_hd(char *str)
{
	char **spltd_str;
	int i;
	int count;

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

int *get_heredoc_content(char *str)
{
	char **spltd_str;
	int i;
	int j;
	int *here_doc;
	int count;

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
void here_doc_process(char **parsed_pipe, int i, int *fd, int *here_doc, int here_doc_index)
{
	int f2;
	char *cmd;

	f2 = open_files_heredoc(parsed_pipe[i]);
	if (not_contain(parsed_pipe[i], '>') || str_str(parsed_pipe[i], ">>"))
	{
		dup2(f2, STD_OUTPUT); //write to file
		close(f2);
	}
	else if (parsed_pipe[i + 1] != NULL && !not_contain(parsed_pipe[i], '>') && !str_str(parsed_pipe[i], ">>"))
	{
		dup2(fd[1], STD_OUTPUT); //write to pipe
		close(fd[1]);
	}
	else if (parsed_pipe[i + 1] == NULL && !not_contain(parsed_pipe[i], '>') && !str_str(parsed_pipe[i], ">>"))
		dup2(1, STD_OUTPUT);				   // write to output
	dup2(here_doc[here_doc_index], STD_INPUT); //here_doc input
	close(here_doc[here_doc_index]);
	cmd = get_cmd_heredoc(parsed_pipe[i]);
	execute_cmd(cmd);
}
//process_redirections(parsed_pipe, i ,fd_in, fd);

void read_from_pipe(char *parsed_pipe, int old_pipe)
{
	int f2;

	if (!not_contain(parsed_pipe, '<'))
	{
		dup2(old_pipe, STD_INPUT); // get input from previous pipe
		if (old_pipe != 0)
			close(old_pipe);
	}
	else if (cmd_contain(parsed_pipe, '<'))
	{
		f2 = get_fd_input(parsed_pipe); // get input from file
		dup2(f2, STD_INPUT);
		close(f2);
	}
}
void process_redirections(char **parsed_pipe, int i, int old_pipe, int *pipe_fd)
{
	int f1;
	int f2;
	char *cmd;

	f1 = open_files(parsed_pipe[i]);
	read_from_pipe(parsed_pipe[i], old_pipe); // or input file
	if (cmd_contain(parsed_pipe[i], '>') || str_str(parsed_pipe[i], ">>"))
	{
		dup2(f1, STD_OUTPUT); // write to ouput file
		close(f1);
	}
	else if (parsed_pipe[i + 1] != NULL && !not_contain(parsed_pipe[i], '>') && !str_str(parsed_pipe[i], ">>"))
		dup2(pipe_fd[1], STD_OUTPUT); // write in pipe // close(fd[1]);
	else if (parsed_pipe[i + 1] == NULL && !cmd_contain(parsed_pipe[i], '>') && !str_str(parsed_pipe[i], ">>"))
		dup2(1, STD_OUTPUT); // write in stdout
	close(pipe_fd[1]);
	cmd = get_cmmd(parsed_pipe[i]);
	execute_cmd(cmd);
}
// process_pipes(parsed_pipe, i, fd, fd_in);
void process_pipes(char **parsed_pipe, int i, int *pipe_fd, int old_pipe)
{
	if (parsed_pipe[i + 1] != NULL)
		dup2(pipe_fd[1], STD_OUTPUT);
	dup2(old_pipe, STD_INPUT);
	if (old_pipe != 0)
		close(old_pipe);
	close(pipe_fd[1]);
	execute_cmd(parsed_pipe[i]);
}
// child_process(parsed_pipe, i, fd, fd_in);
void child_process(char **parsed_pipe, int i, int *pipe, int old_pipe)
{
	close(pipe[0]);
	check_acces(parsed_pipe[i]);
	if ((not_contain(parsed_pipe[i], '<') || not_contain(parsed_pipe[i], '>') || str_str(parsed_pipe[i], ">>")) && !str_str(parsed_pipe[i], "<<"))
		process_redirections(parsed_pipe, i, old_pipe, pipe);
	else
		process_pipes(parsed_pipe, i, pipe, old_pipe);
}

int parent_process(int *fd_pipe, int old_pipe, char **parsed_pipe, int pid, int i)
{
	int status;

	status = 0;
	close(fd_pipe[1]);
	if (old_pipe != 0)
		close(old_pipe);
	old_pipe = fd_pipe[0];
	if (parsed_pipe[i + 1] == NULL)
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			status = WEXITSTATUS(status);
	}
	return (old_pipe);
}

void handlle_pipe(char *str)
{
	char **parsed_pipe;
	int fd[2];
	int pid;
	int fd_in;
	int i;
	int *here_doc;
	int j;

	j = 0;
	fd_in = 0;
	i = 0;
	parsed_pipe = ft_split(str, '|');
	if (str_str(str, "<<"))
		here_doc = check_str(str);

	while (parsed_pipe[i])
	{
		pipe(fd);
		pid = fork();
		if (pid == -1)
			perror("Fork error");
		if (pid == 0)
		{
			close(fd[0]); // read
			if (str_str(parsed_pipe[i], "<<"))
				here_doc_process(parsed_pipe, i, fd, here_doc, j);
			child_process(parsed_pipe, i, fd, fd_in);
		}
		else
		{
			fd_in = parent_process(fd, fd_in, parsed_pipe, pid, i);
			if (str_str(parsed_pipe[i], "<<"))
				j++;
		}
		i++;
	}
	while (wait(NULL) != -1)
	{
	}
}
