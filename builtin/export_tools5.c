/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_tools5.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqadil <aqadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 00:38:07 by aqadil            #+#    #+#             */
/*   Updated: 2022/02/12 01:41:44 by aqadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../aqadil/minishell.h"

void	modify_env_var_value(char *var, char *value)
{
	int		i;
	char	**splited_env;
	char	*result;

	result = ft_strjoin(var, "=");
	result = ft_strjoin(result, value);
	i = 0;
	while (g_env_var.env[i])
	{
		splited_env = ft_split(g_env_var.env[i], '=');
		if (ft_strcmp(splited_env[0], var) == 0)
		{
			free(g_env_var.env[i]);
			g_env_var.env[i] = result;
		}
		i++;
	}
}

void	time_to_export(char *line)
{
	char	*str;
	char	**splited_str;

	str = ft_strtrim(line, " ");
	str = remove_quotes_if_exists(str);
	splited_str = ft_split(str, '=');
	if (var_contain_space(splited_str[0]) == 1)
		printf("export: `=': not a valid identifier\n");
	else
	{
		str = remove_all_quotes(splited_str[1]);
		if (str == NULL)
			return ;
		str = get_export_elem(str);
		if (check_if_not_valid(str) == 1)
			printf("export not valid");
		else
		{
			export_var_to_env(splited_str[0], str);
		}
	}
}

int	check_errors(char *str)
{
	char	**splited;

	if (str[0] == '=')
	{
		printf("export: %s: not a valid identifier\n", str);
		return (0);
	}
	splited = ft_split(str, '=');
	if (splited[1] == NULL)
		return (0);
	if (check_valid_var(splited[0]) == 0)
	{
		printf("export: %s : not a valid identifier\n", splited[0]);
		return (0);
	}
	return (1);
}

int	check_if_not_valid(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (1);
	while (str[i])
	{
		i++;
	}
	return (0);
}

char	*get_export_elem(char *str)
{
	char	**result;

	if (str[0] == ' ')
		return ("\0");
	result = ft_split(str, ' ');
	return (result[0]);
}
