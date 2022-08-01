/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqadil <aqadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 20:42:42 by aqadil            #+#    #+#             */
/*   Updated: 2022/02/22 20:53:33 by aqadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_single_cmd_handler(char *line, char **envp)
{
	char	**args;
	char	*cmd;
	char	*path;
	char	**splited_args;
	int		i;

	i = 0;
	splited_args = bring_args_in(line);
	args = splited_args;
	cmd = splited_args[0];
	cmd = handle_quotes(cmd);
	if (check_and_or_op(args))
	{
		handle_and_or(line);
		return ;
	}
	path = path_search(cmd);
	args = handle_exe_args(args);
	if (check_wild_car(args))
		args = handle_wild_card(line, args);
	if (check_builtin(cmd, args, line, envp))
		;
	else
		time_to_execute(path, cmd, args);
}

char	**handle_exe_args(char **args)
{
	int		i;
	char	*env_v;

	i = 0;
	while (args[i])
	{
		if ((args[i][0] == '\"' && args[i][ft_strlen(args[i]) - 1] == '\"'))
			exe_args_helper(i, args);
		else if ((args[i][0] == '\''
			&& args[i][ft_strlen(args[i]) - 1] == '\''))
		{
			env_v = ft_substr(args[i], 1, ft_strlen(args[i]) - 2);
			free(args[i]);
			args[i] = env_v;
		}
		else if (args[i][0] == '$')
			exe_args_helper1(i, args);
		i++;
	}
	return (args);
}

char	*get_dollar_value(char *str)
{
	int		i;
	char	*resu;

	i = 0;
	while (str[i])
	{
		if (str[i] == ' ' || str[i] == '/')
			break ;
		i++;
	}
	resu = malloc(i + 1);
	if (resu == NULL)
		return (NULL);
	i = 0;
	while (str[i])
	{
		if (str[i] == ' ' || str[i] == '/')
			break ;
		resu[i] = str[i + 1];
		i++;
	}
	resu[i - 1] = 0;
	return (resu);
}

void	execute_single_cmd(char *path, char *cmd, char **args)
{
	pid_t	pid;
	int		status;
	char	*save;
	int		exit_status;
	int		sign;

	exit_status = 0;
	sign = 0;
	save = cmd;
	cmd = ft_strjoin(path, cmd);
	pid = fork();
	if (pid != 0)
		disable_signals();
	if (pid == 0)
	{
		handle_mini_exe();
		if (execve(cmd, args, g_env_var.env))
		{
			printf("%s: No such file or directory\n", save);
			exit(127);
		}
	}
	wait(&status);
	status_helper(status, sign, exit_status);
}

int	check_builtin(char *cmd, char **args, char *line, char **envp)
{
	if (ft_strcmp(cmd, "cd") == 0)
		cd_handler(args, cmd, line);
	else if (ft_strcmp(cmd, "echo") == 0)
		my_echo(line);
	else if (ft_strcmp(cmd, "env") == 0)
		my_env(line, envp);
	else if (ft_strcmp(cmd, "pwd") == 0)
		my_pwd(line);
	else if (ft_strcmp(cmd, "export") == 0)
		my_export(line);
	else if (ft_strcmp(cmd, "exit") == 0)
		my_exit(line);
	else if (ft_strcmp(cmd, "unset") == 0)
		my_unset(line);
	else
		return (0);
	return (1);
}
