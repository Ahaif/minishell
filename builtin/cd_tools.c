/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqadil <aqadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 14:09:23 by aqadil            #+#    #+#             */
/*   Updated: 2022/02/22 20:58:53 by aqadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../aqadil/minishell.h"

int	argument_check(char *path)
{
	char	**splited_path;

	splited_path = ft_split(path, ' ');
	if (splited_path[1] != NULL)
	{
		return (1);
	}
	printf("%s\n", path);
	return (0);
}

char	*env_searcher(char *var)
{
	int		i;
	char	**env_splited;
	char	*var_new;

	var_new = ft_strtrim(var, "$");
	i = 0;
	while (g_env_var.env[i])
	{
		env_splited = ft_split(g_env_var.env[i], '=');
		if (ft_strcmp(var_new, env_splited[0]) == 0)
			return (env_splited[1]);
		i++;
	}
	return (NULL);
}

void	handle_point(char *str)
{
	char	path[PATH_MAX];
	int		i;
	char	**splited;
	char	*pwd;

	(void) str;
	i = 0;
	pwd = get_my_env("PWD");
	if (getcwd(path, sizeof(path)) == NULL)
	{
		printf("cd: error retrieving current directory: getcwd:");
		printf("cannot access parent directories: No such file or directory\n");
		while (g_env_var.env[i])
		{
			splited = ft_split(g_env_var.env[i], '=');
			if (ft_strcmp(splited[0], "PWD") == 0)
				g_env_var.env[i] = ft_strjoin(g_env_var.env[i], "/.");
			else if (ft_strcmp(splited[0], "OLDPWD") == 0)
				g_env_var.env[i] = ft_strjoin("OLDPWD=", pwd);
			i++;
		}
	}
	else
		my_cd(path);
}
