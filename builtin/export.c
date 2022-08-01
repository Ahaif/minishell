/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqadil <aqadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 23:57:53 by aqadil            #+#    #+#             */
/*   Updated: 2022/02/19 15:25:44 by aqadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../aqadil/minishell.h"

int	export_helper2(char *args, int *i, int *check, char *str)
{
	char	*temp;
	char	*var;
	char	*value;

	var = get_export_var(&args[(*i)]);
	value = get_export_value(&args[(*i)]);
	var = remove_quotes_if_exists(var);
	value = remove_quotes_if_exists(value);
	if (var[0] == '\0')
		return (okey());
	if (var == NULL || value == NULL)
		return (0);
	(*check) = check_plus(str);
	if ((*check) == 1)
	{
		var = remove_plus(var);
		var = parse_var(var, value);
		temp = get_my_env(var);
		if (temp != NULL)
			value = ft_strjoin(temp, value);
	}
	export_var_to_env(var, value);
	(*i)++;
	return (1);
}

void	my_export(char *line)
{
	char	**args;
	int		i;
	int		check;

	check = 0;
	i = 0;
	line = remove_export_word(line);
	if (line == NULL)
		return ;
	line = remove_quotes_if_exists(line);
	if (line == NULL)
		return ;
	if (line[0] == '\0')
	{
		handle_solo_export();
		return ;
	}
	args = bring_export_args(line);
	while (args[i])
	{
		if (export_helper2(args[i], &i, &check, line) == 0)
			return ;
	}
	free_double_char(args);
	free(line);
}

char	*remove_plus(char *str)
{
	int		i;
	char	*resu;

	resu = malloc(ft_strlen(str));
	i = 0;
	while (str[i])
	{
		resu[i] = str[i];
		i++;
	}
	resu[i - 1] = 0;
	return (resu);
}

int	check_plus(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=' && str[i - 1] == '+')
			return (1);
		i++;
	}
	return (0);
}

void	export_var_to_env(char *var, char *value)
{
	char	*new_var;
	char	**copy;
	int		i;
	char	*new_value;

	i = 0;
	new_var = parse_var(var, value);
	new_value = value;
	if (new_var == NULL)
		return ;
	if (get_my_env(new_var) != NULL)
		modify_env_var_value(new_var, new_value);
	else
	{
		copy = get_my_env_copy(new_var, new_value);
		free_double_char(g_env_var.env);
		g_env_var.env = copy;
	}
}
