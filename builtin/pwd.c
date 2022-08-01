/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqadil <aqadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 20:38:25 by aqadil            #+#    #+#             */
/*   Updated: 2022/02/22 20:57:26 by aqadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../aqadil/minishell.h"

void	my_pwd(char *line)
{
	int		i;
	char	**env_splited;
	int		j;

	(void) line;
	j = 4;
	i = 0;
	while (g_env_var.env[i])
	{
		env_splited = ft_split(g_env_var.env[i], '=');
		if (ft_strcmp(env_splited[0], "PWD") == 0)
		{
			while (g_env_var.env[i][j])
			{
				printf("%c", g_env_var.env[i][j]);
				j++;
			}
			printf("\n");
			break ;
		}
		free_double_char(env_splited);
		i++;
	}
}
