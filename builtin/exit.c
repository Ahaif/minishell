/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqadil <aqadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 22:09:29 by aqadil            #+#    #+#             */
/*   Updated: 2022/02/19 15:24:34 by aqadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../aqadil/minishell.h"

int	get_code(char *line)
{
	int		code;
	char	**args;

	args = ft_split(line, ' ');
	if (args[1] == NULL)
		return (0);
	code = ft_atoi(args[1]);
	free_double_char(args);
	return (code);
}

void	exit_helper1(char **splited, char *line)
{
	printf("exit\n");
	printf("exit: %s: numeric argument required\n", line);
	free_double_char(splited);
	exit(255);
}

void	my_exit(char *line)
{
	int		code;
	char	**splited;

	splited = ft_split(line, ' ');
	dec_bash_lvl();
	if (splited[1] == NULL)
		time_to_exit();
	if (isalpha(splited[1][0]))
		exit_helper1(splited, line);
	if (splited[2] != NULL)
	{
		free_double_char(splited);
		printf("exit\nexit: too many arguments\n");
		return ;
	}
	free_double_char(splited);
	printf("exit\n");
	code = get_code(line);
	if (code != 0)
		exit(code);
	exit(0);
}

int	get_status_code(int status)
{
	int	exit_status;

	exit_status = WEXITSTATUS(status);
	return (exit_status);
}

void	time_to_exit(void)
{
	printf("exit\n");
	exit(0);
}
