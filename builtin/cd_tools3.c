/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_tools3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqadil <aqadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 22:45:27 by aqadil            #+#    #+#             */
/*   Updated: 2022/02/14 19:08:12 by aqadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../aqadil/minishell.h"

void	cd_helper(char *home)
{
	if (home == NULL)
	{
		printf("cd: HOME not set\n");
		g_env_var.status = 1;
	}
	else
		my_cd(home);
}

int	get_cd_path(char *str)
{
	t_vars	var;

	var_init(&var);
	while (str[var.i])
	{
		if (str[var.i] == '\"')
		{
			if (var.double_quote > 0)
				var.double_quote--;
			else
				var.double_quote++;
			var.i++;
		}
		if (str[var.i] == '\'')
		{
			if (var.single_quote > 0 && var.i++)
				var.single_quote--;
			else
				var.single_quote++;
		}
		if (str[var.i] == ' ' && var.double_quote == 0 && var.single_quote == 0)
			return (var.i);
		var.i++;
	}
	return (var.i);
}
