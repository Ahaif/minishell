/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqadil <aqadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 01:04:45 by aqadil            #+#    #+#             */
/*   Updated: 2022/02/12 01:43:55 by aqadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*path_search(char *cmd)
{
	char	**str;
	char	*env;
	char	*path;
	char	*path_search;
	int		i;

	i = 0;
	env = get_my_env("PATH");
	if (env == NULL)
		return (NULL);
	str = ft_split(env, ':');
	while (str[i])
	{
		path = ft_strjoin(str[i], "/");
		path_search = ft_strjoin(path, cmd);
		if (access(path_search, X_OK) == 0)
			return (path);
		i++;
	}
	return (NULL);
}

void	time_to_execute(char *path, char *cmd, char **args)
{
	if (path == NULL)
	{
		printf("%s : command not found\n", cmd);
		g_env_var.status = 127;
	}
	else
		execute_single_cmd(path, cmd, args);
}

void	exe_args_helper(int i, char **args)
{
	char	*env_v;
	char	*temp;
	char	*rest;
	char	*var;

	env_v = ft_substr(args[i], 1, ft_strlen(args[i]) - 2);
	if (env_v[0] == '$')
	{
		temp = get_dollar_value(env_v);
		var = get_my_env(temp);
		rest = ft_substr(env_v, ft_strlen(temp) + 1, ft_strlen(env_v));
		env_v = ft_strjoin(var, rest);
	}
	free(args[i]);
	args[i] = env_v;
}

void	exe_args_helper1(int i, char **args)
{
	char	*env_v;
	char	*temp;
	char	*rest;

	temp = get_dollar_value(args[i]);
	env_v = get_my_env(temp);
	rest = ft_substr(args[i], ft_strlen(temp) + 1, ft_strlen(args[i]));
	env_v = ft_strjoin(env_v, rest);
	free(args[i]);
	args[i] = env_v;
}

void	status_helper(int status, int sign, int exit_status)
{
	if (WIFSIGNALED(status))
	{
		printf("\n");
		sign = 128 + status;
	}
	disable_signals_terminos();
	exit_status = get_status_code(status);
	g_env_var.status = exit_status + sign;
}
