/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqadil <aqadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 00:02:37 by aqadil            #+#    #+#             */
/*   Updated: 2022/02/22 20:59:56 by aqadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../aqadil/minishell.h"

void	export_helper(char *line, int *i, int *start, int *end)
{
	int	save;

	(void) start;
	if (line[(*i) + 1] == '\'' || line[(*i) + 1] == '\"')
	{
		(*i)++;
		save = (*i);
		(*i)++;
		while (line[(*i)] != line[save])
			(*i)++;
		(*end) = (*i) + 1;
	}
	else
	{
		while (line[(*i)] != ' ')
			(*i)++;
		(*end) = (*i);
	}
}

void	end_bring_export_args(char **args, int j, char *line)
{
	args[j] = 0;
	if (args[0] == NULL)
		parse_var(line, "");
}

char	**bring_export_args(char *line)
{
	char	**args;
	t_vars	var;

	var_init(&var);
	args = malloc((count_export_args(line) + 1) * sizeof(char *));
	while (line[var.i])
	{
		if (var.i == 0)
			var.start = var.i;
		else if (var.start == -1 && (ft_isalnum(line[var.i]) == 1
				|| line[var.i] == '\'' || line[var.i] == '\"'))
			var.start = var.i;
		if (line[var.i] == '=')
			export_helper(line, &var.i, &var.start, &var.end);
		if (var.start != -1 && var.end != -1)
		{
			args[var.j] = ft_substr(line, var.start, var.end - var.start);
			var.j++;
			var.start = -1;
			var.end = -1;
		}
		var.i++;
	}
	end_bring_export_args(args, var.j, line);
	return (args);
}

void	count_export_helper(char *line, int *i, int *end)
{
	int	save;

	if (line[(*i) + 1] == '\'' || line[(*i) + 1] == '\"')
	{
		(*i)++;
		save = (*i);
		i++;
		while (line[(*i)] != line[save])
			(*i)++;
		(*end) = (*i) + 1;
	}
	else
	{
		while (line[(*i)] != ' ')
			(*i)++;
		(*end) = (*i);
	}
}

int	count_export_args(char *line)
{
	int		count;
	t_vars	var;

	var_init(&var);
	count = 0;
	while (line[var.i])
	{
		if (var.i == 0)
			var.start = var.i;
		else if (var.start == -1 && ft_isalpha(line[var.i]) == 1)
			var.start = var.i;
		if (line[var.i] == '=')
			count_export_helper(line, &var.i, &var.end);
		if (var.start != -1 && var.end != -1)
		{
			count++;
			var.start = -1;
			var.end = -1;
		}
		var.i++;
	}
	return (count);
}
