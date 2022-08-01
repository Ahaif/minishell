/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_tools2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqadil <aqadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 22:28:04 by aqadil            #+#    #+#             */
/*   Updated: 2022/02/22 21:04:44 by aqadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../aqadil/minishell.h"

int	not_single_quoted(char *str)
{
	if (str[0] != '\'' && str[ft_strlen(str) - 1] != '\'')
		return (1);
	return (0);
}

void	handle_double_minus(char *path)
{
	char	*home_path;

	home_path = get_my_env("HOME");
	if (access(home_path, R_OK))
	{
		printf("cd: permission denied: %s\n", path);
		g_env_var.status = 1;
	}
	else
		my_cd(home_path);
}

void	my_cd_v1(char *str, char *path, char *home)
{
	if (str == NULL)
	{
		g_env_var.status = 1;
		return ;
	}
	if (path == NULL)
		my_cd("/");
	else if (ft_strcmp(str, "--") == 0)
		handle_double_minus(str);
	else if (ft_strcmp(str, "-") == 0)
		handle_single_minus(str);
	else if (ft_strcmp(str, ".") == 0)
		handle_point(str);
	else if (cmd_contain(str, '$') && not_single_quoted(path))
		handle_cd_dollar(str);
	else
		my_cd_v2(str, path, home);
}

void	my_cd_v2(char *str, char *path, char *home)
{
	(void )path;
	if (str[0] == '~')
	{
		home = get_my_env("HOME");
		str = ft_strjoin(home, &str[1]);
	}
	if (access(str, F_OK))
	{
		printf("cd: %s: No such file or directory\n", str);
		g_env_var.status = 1;
	}
	else if (access(str, R_OK))
	{
		printf("cd: %s: Permission denied: \n", str);
		g_env_var.status = 1;
	}
	else
	{
		chane_old_pwd(str);
		chdir(str);
		change_pwd(str);
		g_env_var.status = 0;
	}
}

void	handle_cd_dollar(char *path)
{
	char	*upper;
	char	*value;

	(void )path;
	upper = NULL;
	value = env_searcher(upper);
	if (value == NULL)
		;
	else
		my_cd(value);
}
