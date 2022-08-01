/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqadil <aqadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 00:38:18 by aqadil            #+#    #+#             */
/*   Updated: 2022/02/23 02:02:33 by aqadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../aqadil/minishell.h"

void	handle_single_minus(char *path)
{
	char	**env_splited;
	int		i;

	(void) path;
	i = 0;
	if (old_path_not_set() == 1)
	{
		g_env_var.status = 1;
		printf("cd: OLDPWD not set\n");
	}
	while (g_env_var.env[i])
	{
		env_splited = ft_split(g_env_var.env[i], '=');
		if (ft_strcmp("OLDPWD", env_splited[0]) == 0)
		{
			my_cd(env_splited[1]);
			printf("%s\n", env_splited[1]);
			free_double_char(env_splited);
			return ;
		}
		free_double_char(env_splited);
		i++;
	}
}

void	change_pwd(char *path)
{
	char	**env_splited;
	int		i;
	char	pwd[PATH_MAX];

	(void) path;
	i = 0;
	getcwd(pwd, sizeof(pwd));
	while (g_env_var.env[i])
	{
		env_splited = ft_split(g_env_var.env[i], '=');
		if (ft_strcmp(env_splited[0], "PWD") == 0)
		{
			free(g_env_var.env[i]);
			g_env_var.env[i] = ft_strjoin("PWD=", pwd);
		}
		free_double_char(env_splited);
		i++;
	}
}

void	chane_old_pwd(char *path)
{
	char	**env_splited;
	int		i;
	char	pwd[PATH_MAX];

	(void) path;
	if (old_path_not_set() == 1)
	{
		set_old_path();
		return ;
	}
	getcwd(pwd, sizeof(pwd));
	i = 0;
	while (g_env_var.env[i])
	{
		env_splited = ft_split(g_env_var.env[i], '=');
		if (ft_strcmp(env_splited[0], "OLDPWD") == 0)
		{
			free(g_env_var.env[i]);
			g_env_var.env[i] = ft_strjoin("OLDPWD=", pwd);
		}
		free_double_char(env_splited);
		i++;
	}
}

void	my_cd(char *path)
{
	char	*str;
	char	*home;
	int		check;

	home = NULL;
	check = 0;
	if (path[0] == '\0')
	{
		g_env_var.status = 0;
		return ;
	}
	str = remove_quotes_if_exists(path);
	if (str == NULL)
	{
		g_env_var.status = 1;
		return ;
	}
	my_cd_v1(str, path, home);
}

void	cd_handler(char **args, char *cmd, char *line)
{
	char	*home;
	char	*path;
	int		index;
	int		i;

	(void) cmd;
	line = ft_substr(line, 3, ft_strlen(line) - 2);
	index = get_cd_path(line);
	path = ft_substr(line, 0, index);
	args = bring_args_in(path);
	args = handle_exe_args(args);
	i = 1;
	path = args[0];
	while (args[i])
	{
		path = ft_strjoin(path, args[i]);
		i++;
	}
	home = get_my_env("HOME");
	if (args[0] == NULL)
		cd_helper(home);
	else
		my_cd(path);
}
