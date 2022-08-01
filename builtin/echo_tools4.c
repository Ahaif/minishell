/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_tools4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqadil <aqadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 14:46:44 by aqadil            #+#    #+#             */
/*   Updated: 2022/02/14 19:36:13 by aqadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../aqadil/minishell.h"

void	place_arg(char **args, char *str, int start, int end)
{
	char	*string;
	int		i;

	i = 0;
	string = ft_substr(str, start + 1, end - start);
	while (args[i])
		i++;
	args[i] = string;
	args[i + 1] = 0;
}

int	line_arg_count_h_1(char *str, int i, int *count)
{
	while (str[i + 1] != '\'' && str[i + 1])
		i++;
	if (str[i + 1] != '\'')
		return (0);
	i++;
	(*count)++;
	return (i);
}

int	line_arg_count(char *str)
{
	t_vars	var;

	var_init(&var);
	if (str == NULL)
		return (1);
	while (str[var.i])
	{
		if (str[var.i] == '\'' && var.double_quote == 0)
		{
			var.i = line_arg_count_h_1(str, var.i, &(var.count));
			if (var.i == 0)
				return (0);
		}
		if (str[var.i] == '\"' && var.single_quote == 0)
		{
			var.i = line_arg_count_h_3(str, var.i, &(var.count));
			if (var.i == 0)
				return (0);
		}
		if (var.single_quote == 0 && var.double_quote == 0 && str[var.i] != '\''
			&& str[var.i] != '\"' && str[var.i] != ' ')
			var.i = line_arg_count_h_2(str, var.i, &(var.count));
		var.i++;
	}
	return (var.count);
}

int	place_help_s_q_1(char **args, int i, char *str)
{
	int	start;
	int	end;

	start = i;
	while (str[i + 1] != '\'' && str[i + 1])
		i++;
	end = i;
	place_arg(args, str, start - 1, end + 1);
	i++;
	return (i);
}

int	place_help_s_q_2(char **args, int i, char *str)
{
	int	start;
	int	end;

	start = i;
	while (str[i + 1] != '\"' && str[i + 1])
		i++;
	end = i;
	place_arg(args, str, start - 1, end + 1);
	i++;
	return (i);
}
