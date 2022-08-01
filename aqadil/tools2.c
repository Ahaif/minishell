/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqadil <aqadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 01:04:57 by aqadil            #+#    #+#             */
/*   Updated: 2022/02/23 02:01:55 by aqadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dec_bash_lvl(void)
{
	int		i;
	char	**name;
	int		lvl;
	char	*newlvl;

	i = 0;
	while (g_env_var.env[i])
	{
		name = ft_split(g_env_var.env[i], '=');
		if (ft_strcmp(name[0], "SHLVL") == 0)
		{
			lvl = ft_atoi(name[1]);
			newlvl = ft_itoa(--lvl);
			free(g_env_var.env[i]);
			g_env_var.env[i] = ft_strjoin("SHLVL=", newlvl);
			break ;
		}
		i++;
	}
}

void	inc_bash_lvl(void)
{
	int		i;
	char	**name;
	int		lvl;
	char	*newlvl;

	i = 0;
	while (g_env_var.env[i])
	{
		name = ft_split(g_env_var.env[i], '=');
		if (ft_strcmp(name[0], "SHLVL") == 0)
		{
			lvl = ft_atoi(name[1]);
			newlvl = ft_itoa(++lvl);
			free(g_env_var.env[i]);
			g_env_var.env[i] = ft_strjoin("SHLVL=", newlvl);
			break ;
		}
		i++;
	}
}

void	helper3_3(t_vars *var)
{
	var->or = 1;
	var->end = var->i++;
}

void	redirec_child_process(char *str, int f2, int f1)
{
	char	*cmd;

	if (str_str(str, "<<"))
		cmd = get_cmd_heredoc(str);
	else
		cmd = get_cmmd(str);
	if (str_str(str, "<<"))
	{
		dup2(f2, STD_INPUT);
		close(f2);
	}
	if (cmd_contain(str, '<'))
		dup2(f2, STD_INPUT);
	dup2(f1, STD_OUTPUT);
	close(f2);
	check_acces(cmd);
	execute_cmd(cmd);
}

void	handlle_redirections(char *str)
{
	int	f1;
	int	pid;
	int	f2;

	if (str_str(str, "<<"))
	{
		f2 = open_heredoc(str);
		f1 = open_files_heredoc(str);
	}
	else
	{
		f1 = open_files(str);
		if (cmd_contain(str, '<'))
			f2 = get_fd_input(str);
	}
	pid = fork();
	if (pid == -1)
		return (perror("Fork error"));
	if (pid == 0)
		redirec_child_process(str, f2, f1);
	else
		wait(NULL);
}
