/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqadil <aqadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 14:34:16 by aqadil            #+#    #+#             */
/*   Updated: 2022/02/22 20:59:20 by aqadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../aqadil/minishell.h"

int	check_echo_option(char *line)
{
	char	**line_splited;

	line_splited = ft_split(line, ' ');
	if (line_splited[1] == NULL)
		return (0);
	if (line_splited[1][0] == '-' && line_splited[1][1] == 'n')
	{
		free_double_char(line_splited);
		return (1);
	}
	free_double_char(line_splited);
	return (0);
}

char	*remove_dollar(char *str)
{
	char	*result;
	int		i;

	i = 0;
	result = malloc(ft_strlen(str));
	if (result == NULL)
		return (NULL);
	while (str[i])
	{
		result[i] = str[i + 1];
		i++;
	}
	return (result);
}

int	print_env(int start, int end, char *arg)
{
	char	*result;

	result = ft_substr(arg, start, end - start);
	if (result[1] == '=')
		echo_helpr_3(result);
	else if (result[1] == '\0')
		write(1, "$", 1);
	else if (ft_strcmp(result, "$?") == 0)
	{
		ft_putnbr(g_env_var.status);
		return (1);
	}
	else if (result[1] == '?')
		echo_helper_2(result);
	else if (result[1] >= '0' && result[1] <= '9')
		echo_helper_1(result);
	if (result[0] == '$' && isalpha(result[1]) == 0)
		;
	else
	{
		if (echo_helper_5(result) == 0)
			return (0);
	}
	free(result);
	return (1);
}

int	check_surrounded(char *str, int pos)
{
	t_vars	var;

	pos = 0;
	var_init(&var);
	while (str[var.i])
	{
		if (str[var.i] == '\'')
		{
			var.double_quote = 0;
			var.single_quote++;
		}
		if (str[var.i] == '\"')
		{
			var.single_quote = 0;
			var.double_quote++;
		}
		var.i++;
	}
	if (var.double_quote == 0 && var.single_quote == 0)
		return (1);
	if (var.double_quote == 0)
		return (0);
	return (1);
}
