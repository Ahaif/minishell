/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_tools3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqadil <aqadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 22:26:47 by aqadil            #+#    #+#             */
/*   Updated: 2022/02/12 01:41:33 by aqadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../aqadil/minishell.h"

int	count_my_env(void)
{
	int	i;

	i = 0;
	while (g_env_var.env[i])
		i++;
	return (i);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_isalpha(char c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a'
			&& c <= 'z') || (c == '-' || c == '_'))
		return (1);
	return (0);
}

int	check_valid_var(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if ((ft_isalpha(str[i]) == 0) && ft_isdigit(str[0]) == 1)
			return (0);
		i++;
	}
	return (1);
}

int	quote_is_open(char *line, int start, int i)
{
	while (start <= i && line[start])
	{
		if (line[start] == '=')
		{
			if ((line[start + 1] == '\"' || line[start + 1] == '\'')
				&& (line[i] != '\"' || line[i] != '\''))
				return (1);
		}
		start++;
	}
	return (0);
}
