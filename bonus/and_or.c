/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and_or.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqadil <aqadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 00:18:49 by aqadil            #+#    #+#             */
/*   Updated: 2022/02/21 20:55:36 by aqadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../aqadil/minishell.h"

void	and_or_exe(char **args, char *which_op)
{
	int	i;

	i = 0;
	while (args[i])
	{
		if (i == 0)
			execute_single_cmd_handler(args[i], g_env_var.env);
		else if (which_op[i - 1] == '&')
		{
			if (g_env_var.status == 0)
				execute_single_cmd_handler(args[i], g_env_var.env);
		}
		else if (which_op[i - 1] == '|')
		{
			if (g_env_var.status != 0)
				execute_single_cmd_handler(args[i], g_env_var.env);
		}
		i++;
	}
}

int	count_args_witout_op(char **args)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (args[i])
	{
		if (args[i][0] != '&' && args[i][1] != '&'
			&& args[i][0] != '|' && args[i][0] != '|')
			count++;
		i++;
	}
	return (count);
}

void	handle_and_or(char *line)
{
	char	**args;
	char	*which_op;
	int		i;
	char	*str;

	i = 0;
	str = parse_line(line);
	if (str[ft_strlen(str) - 1] == '&' || str[ft_strlen(str) - 1] == '|')
	{
		printf("Syntax error\n");
		return ;
	}
	args = bring_commandes_in(str);
	which_op = bring_which_op(line, args);
	and_or_exe(args, which_op);
}

char	*bring_which_op(char *line, char **args)
{
	char	*which_op;
	t_vars	var;

	var.count = count_args_witout_op(args);
	which_op = malloc(var.count);
	b_init(&var, line);
	while (line[var.i])
	{
		if (var.i == 0)
			var.start = 0;
		else if (var.start == -1)
			var.start = var.i;
		if ((line[var.i] == '&' && line[var.i + 1] == '&')
			&& (and_or_not_quoted(line, var.i) == 0))
			helper2_2(&var);
		else if ((line[var.i] == '|' && line[var.i] == '|')
			&& (and_or_not_quoted(line, var.i) == 0))
			helper3_3(&var);
		else if (var.i == ft_strlen(line) - 1)
			var.end = var.i + 1;
		if (var.i++ && var.start != -1 && var.end != -1)
			helper1_1(&var, which_op);
	}
	which_op[var.j] = 0;
	return (which_op);
}

int	and_or_not_quoted(char *str, int index)
{
	t_vars	var;

	var_init(&var);
	while (var.i <= index)
	{
		if (str[var.i] == '\"' && var.single_quote == 0
			&& var.double_quote == 0)
		{
			var.double_quote = 1;
			var.i++;
		}
		else if (str[var.i] == '\'' && var.double_quote == 0
			&& var.single_quote == 0)
			help3_3_3(&var);
		if (var.double_quote > 0 && str[var.i] == '\"')
			var.double_quote = 0;
		else if (var.single_quote > 0 && str[var.i] == '\'')
			var.single_quote = 0;
		var.i++;
	}
	if (var.double_quote == 0 && var.single_quote == 0)
		return (0);
	return (1);
}
