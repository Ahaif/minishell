/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqadil <aqadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 00:53:38 by aqadil            #+#    #+#             */
/*   Updated: 2022/02/12 01:41:56 by aqadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../aqadil/minishell.h"

int	ft_isalnum(int c)
{
	if ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z')
		|| (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}

int	check_alpha_n(char *env_name)
{
	int	i;

	i = 0;
	while (env_name[i])
	{
		if (ft_isalnum(env_name[i]) == 0 && env_name[i]
			!= '_' && env_name[i] != '$')
			return (0);
		i++;
	}
	return (1);
}

char	*remove_unset(char *line)
{
	char	*result;

	result = ft_strtrim(line, " ");
	result = ft_substr(result, 5, ft_strlen(result));
	result = ft_strtrim(result, " ");
	return (result);
}

void	handle_solo_export(void)
{
	int	i;

	i = 0;
	while (g_env_var.env[i])
	{
		printf("declare -x %s\n", g_env_var.env[i]);
		i++;
	}
}
