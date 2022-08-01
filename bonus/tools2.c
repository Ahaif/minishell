/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqadil <aqadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 16:14:03 by aqadil            #+#    #+#             */
/*   Updated: 2022/02/21 19:10:17 by aqadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../aqadil/minishell.h"

int	count_line(char *line)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] != ')' && line[i] != '(')
			count++;
		i++;
	}
	return (count);
}

char	*parse_line(char *line)
{
	int		i;
	char	*str;
	int		j;

	j = 0;
	str = malloc(count_line(line) + 1);
	i = 0;
	while (line[i])
	{
		if (line[i] != '(' && line[i] != ')')
		{
			str[j] = line[i];
			j++;
		}
		i++;
	}
	return (str);
}

int	count_commands(char *line)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == '&' && line[i + 1] == '&')
			count++;
		else if (line[i] == '|' && line[i + 1] == '|')
			count++;
		i++;
	}
	return (count);
}

int	check_and_or_op(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		if (args[i][0] == '&' && args[i][1] == '&')
			return (1);
		if (args[i][0] == '|' && args[i][1] == '|')
			return (1);
		i++;
	}
	return (0);
}

void	helper2_2(t_vars *var)
{
	var->and = 1;
	var->end = var->i++;
}
