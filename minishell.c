/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqadil <aqadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 16:01:05 by aqadil            #+#    #+#             */
/*   Updated: 2022/02/23 02:29:45 by aqadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./aqadil/minishell.h"

int	old_path_not_set(void)
{
	int		i;
	char	**env_splited;

	i = 0;
	while (g_env_var.env[i])
	{
		env_splited = ft_split(g_env_var.env[i], '=');
		if (ft_strcmp("OLDPWD", env_splited[0]) == 0)
		{
			free_double_char(env_splited);
			return (0);
		}
		free_double_char(env_splited);
		i++;
	}
	return (1);
}

void	set_old_path(void)
{
	int		i;
	char	path[PATH_MAX];

	getcwd(path, sizeof(path));
	i = 0;
	while (g_env_var.env[i])
		i++;
	g_env_var.env[i] = ft_strjoin("OLDPWD=", path);
}

void	show_prompt(void)
{
	char	*str;

	str = readline("\033[0;36m-> minishell : \033[0m");
	if (str == NULL)
	{
		printf("exit\n");
		exit(1);
	}
	if (grammer_check(str) == 1)
	{
		free(str);
		return ;
	}
	else
		parser_and_execute(str);
}

void	making_fun(void)
{
	execute_single_cmd_handler("clear", g_env_var.env);
	usleep(500000);
	printf("\033[1;31m");
	printf("******************************************");
	usleep(500000);
	printf("\033[1;31m");
	printf("\n\n\n\t****** MINI SHELL ******");
	usleep(500000);
	printf("\n\n\t-BY AQADIL  &  AHAIFOUL-");
	printf("\033[1;31m");
	printf("\n\n\n\n******************************************");
	usleep(500000);
	printf("\033[0m");
	printf("\n\n\nHAVE FUN :D\n");
	printf("\n");
	sleep(1);
}

int	main(int argc, char **argv, char **envp)
{
	if (argc && argv)
		;
	disable_signals_terminos();
	get_copy(envp);
	inc_bash_lvl();
	making_fun();
	while (1)
	{
		show_prompt();
	}
	free_double_char(g_env_var.env);
	enable_signals_and_terminos();
	rl_clear_history();
	return (0);
}
