/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqadil <aqadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 20:48:01 by aqadil            #+#    #+#             */
/*   Updated: 2022/02/21 20:58:10 by aqadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../aqadil/minishell.h"

void	helper1_1(t_vars *var, char *which_op)
{
	if (var->and == 1)
			which_op[var->j] = '&';
	else if (var->or == 1)
		which_op[var->j] = '|';
	var->j++;
	var->start = -1;
	var->end = -1;
	var->and = 0;
	var->or = 0;
}

void	b_init(t_vars *var, char *line)
{
	var->j = 0;
	var->count = count_commands(line) + 1;
	var->args = malloc((var->count + 1) * sizeof(char *));
	var->start = -1;
	var->end = -1;
	var->i = 0;
	var->and = 0;
	var->or = 0;
}

void	bring_cmd_helper(t_vars *var)
{
	var->j++;
	var->start = -1;
	var->end = -1;
}

char	**bring_commandes_in(char *line)
{
	t_vars	var;

	b_init(&var, line);
	while (line[var.i])
	{
		if (var.i == 0)
			var.start = 0;
		else if (var.start == -1)
			var.start = var.i;
		if (((line[var.i] == '&' && line[var.i + 1] == '&')
				|| (line[var.i] == '|' && line[var.i] == '|'))
			&& (and_or_not_quoted(line, var.i) == 0))
			var.end = var.i++;
		else if (var.i == ft_strlen(line) - 1)
			var.end = var.i + 1;
		if (var.start != -1 && var.end != -1)
		{
			var.args[var.j] = ft_substr(line, var.start, var.end - var.start);
			bring_cmd_helper(&var);
		}
		var.i++;
	}
	var.args[var.j] = 0;
	return (var.args);
}

void	help3_3_3(t_vars *var)
{
	var->single_quote = 1;
	var->i++;
}
