/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqadil <aqadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 21:30:10 by aqadil            #+#    #+#             */
/*   Updated: 2022/02/12 01:25:26 by aqadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_multiple_cmd(char *str, char **envp)
{
	char	**cmd_split;
	int		i;

	i = 0;
	cmd_split = ft_split(str, ';');
	while (cmd_split[i])
	{
		execute_single_cmd_handler(cmd_split[i], envp);
		i++;
	}
}

int	arg_count(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}
