/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqadil <aqadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 17:04:00 by aqadil            #+#    #+#             */
/*   Updated: 2022/02/14 19:47:49 by aqadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../aqadil/minishell.h"

char	*get_my_env(char *env_name)
{
	int		i;
	char	**env_splited;
	char	*result;

	i = 0;
	while (g_env_var.env[i])
	{
		env_splited = ft_split(g_env_var.env[i], '=');
		if (ft_strcmp(env_splited[0], env_name) == 0)
		{
			result = ft_strdup(env_splited[1]);
			free_double_char(env_splited);
			return (result);
		}
		i++;
	}
	return (NULL);
}
