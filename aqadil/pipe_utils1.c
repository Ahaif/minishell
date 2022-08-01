/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqadil <aqadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 16:56:16 by ahaifoul          #+#    #+#             */
/*   Updated: 2022/02/23 02:44:18 by aqadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redirect_input(char **parsed_pipe, int i, int *fd_pp)
{
	int	fd_in1;

	(void )fd_pp;
	fd_in1 = 0;
	fd_in1 = get_fd_input(parsed_pipe[i]);
	dup2(fd_in1, STD_INPUT);
	execute_cmd(get_cmd(parsed_pipe[i]));
	exit(0);
}

char	**get_path(void)
{
	char	*path_from_envp;
	char	**spltd_paths;

	path_from_envp = get_my_env("PATH");
	spltd_paths = ft_split(path_from_envp, ':');
	return (spltd_paths);
}

int	check_access(char *str)
{
	char	**spltd_paths;
	char	**cmd_options;
	char	*access_par;
	int		i;
	int		ret;

	cmd_options = ft_split(str, ' ');
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

void	execute_cmd(char *str)
{
	execute_handler(str);
	exit(0);
}

int	open_append_mode(char *str)
{
	char	**spltd_str;
	char	*temp;
	int		f1;

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
