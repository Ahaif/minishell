/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqadil <aqadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 15:48:09 by aqadil            #+#    #+#             */
/*   Updated: 2022/02/22 20:57:08 by aqadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../aqadil/minishell.h"

char	*get_first_arg(char *line)
{
	char	**str;

	str = ft_split(line, ' ');
	return (str[1]);
}

int	env_checker(char *line)
{
	char	**args;

	args = ft_split(line, ' ');
	if (args[1] != NULL)
	{
		free_double_char(args);
		return (1);
	}
	return (0);
}

int	count_lines(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	return (i);
}

void	get_copy(char **envp)
{
	int		lines;
	int		i;
	int		j;
	char	**s;

	i = 0;
	j = 0;
	lines = count_lines(envp);
	g_env_var.env = (char **)malloc((lines + 2) * sizeof(char *));
	if (g_env_var.env == NULL)
		return ;
	while (envp[i])
	{
		s = ft_split(envp[i], '=');
		if (ft_strcmp(s[0], "OLDPWD") == 0)
			envp[i] = envp[i + 1];
		g_env_var.env[i] = ft_strdup(envp[i]);
		free_double_char(s);
		i++;
	}
	g_env_var.env[i] = 0;
	g_env_var.env[i + 1] = 0;
}

void	my_env(char *line, char **envp)
{
	int		i;
	char	*str;

	(void) *envp;
	i = 0;
	str = get_first_arg(line);
	if (env_checker(line))
	{
		printf("env: \'%s\': No such file or directory\n", str);
		return ;
	}
	while (g_env_var.env[i])
	{
		printf("%s\n", g_env_var.env[i]);
		i++;
	}
	free(str);
}
