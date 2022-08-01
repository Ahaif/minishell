/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_splited.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqadil <aqadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 17:54:37 by aqadil            #+#    #+#             */
/*   Updated: 2022/02/23 02:16:21 by aqadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_quotes_open(char *str, int i, int index_finish)
{
	t_vars	var;

	var_init(&var);
	while (i <= index_finish)
	{
		if (str[i] == '\"' && var.single_quote == 0 && var.double_quote == 0)
		{
			var.double_quote = 1;
			i++;
		}
		if (str[i] == '\'' && var.double_quote == 0 && var.single_quote == 0)
		{
			var.single_quote = 1;
			i++;
		}
		if (str[i] == '\"' && var.double_quote == 1)
			var.double_quote = 0;
		if (str[i] == '\'' && var.single_quote == 1)
			var.single_quote = 0;
		i++;
	}
	if (var.single_quote > 0 || var.double_quote > 0)
		return (1);
	return (0);
}

int	ft_pipe_counter(char *str)
{
	int		i;
	t_vars	var;

	var_init(&var);
	i = -1;
	while (str[++i])
	{
		if (var.start == -1)
			var.start = i;
		if ((str[i] == '|' && check_quotes_open(str, 0, i) == 0)
			|| str[i + 1] == '\0')
		{
			var.end = i;
			if (str[i + 1] == '\0')
				var.end++;
		}
		if (var.end != -1)
		{
			var.pipe_counter++;
			var.end = -1;
			var.start = -1;
		}
	}
	return (var.pipe_counter);
}

void	blabla(t_vars *var)
{
	if (var->result[var->j][0] == '\"')
		var->result[var->j] = ft_strtrim(var->result[var->j], "\"");
	var->end = -1;
	var->start = -1;
	var->j++;
}

char	**pipe_spliter(char *str)
{
	t_vars	var;

	var_init(&var);
	var.result = malloc((ft_pipe_counter(str) + 1) * sizeof(char *));
	while (str[var.i])
	{
		if (var.start == -1)
			var.start = var.i;
		if ((str[var.i] == '|' && check_quotes_open(str, 0, var.i) == 0)
			|| str[var.i + 1] == '\0')
		{
			var.end = var.i;
			if (str[var.i + 1] == '\0')
				var.end++;
		}
		if (var.i++ && var.end != -1)
		{
			var.result[var.j] = ft_strtrim(ft_substr(str,
						var.start, var.end - var.start), " ");
			blabla(&var);
		}
	}
	var.result[var.j] = 0;
	return (var.result);
}
