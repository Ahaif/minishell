/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqadil <aqadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 00:21:53 by aqadil            #+#    #+#             */
/*   Updated: 2022/02/19 15:36:47 by aqadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../aqadil/minishell.h"

int	place_help_s_q_3(char **args, int i, char *str)
{
	int	start;
	int	end;

	start = i - 1;
	while (str[i + 1] != '\'' && str[i + 1]
		!= '\"' && str[i + 1] != ' ' && str[i + 1])
		i++;
	end = i;
	place_arg(args, str, start, end);
	return (i);
}

char	**bring_args_in(char *str)
{
	int		count;
	char	**args;
	t_vars	var;

	var_init(&var);
	count = line_arg_count(str);
	args = malloc((count + 1) * sizeof(char *));
	if (args == NULL)
		return (NULL);
	args[0] = 0;
	while (str[var.i])
	{
		if (str[var.i] == '\'' && var.double_quote == 0)
			var.i = place_help_s_q_1(args, var.i, str);
		if (str[var.i] == '\"' && var.single_quote == 0)
			var.i = place_help_s_q_2(args, var.i, str);
		if (var.single_quote == 0 && var.double_quote == 0 && str[var.i]
			!= '\'' & str[var.i] != '\"' && str[var.i] != ' ')
			var.i = place_help_s_q_3(args, var.i, str);
		var.i++;
	}
	return (args);
}

char	*remove_echo(char *str, int option_check)
{
	char	*result;
	int		i;
	char	*trimed_result;

	i = -1;
	if (str[0] == '\"' || str[0] == '\'')
		result = ft_substr(str, 6, ft_strlen(str) - 4);
	else
		result = ft_substr(str, 4, ft_strlen(str) - 4);
	trimed_result = ft_strtrim(result, " ");
	free(result);
	if (option_check == 1)
	{
		trimed_result = handle_option_check(trimed_result);
	}
	return (trimed_result);
}

char	*handle_option_check(char *result)
{
	int		i;
	char	*result2;
	char	*trimed_result;

	result2 = result;
	i = -1;
	while (result2[++i])
	{
		if (result2[i] == '-' && result2[i + 1] == 'n')
		{
			if (result2[i + 2] == '-')
				break ;
			while (result2[i + 1] == 'n')
				i++;
			result2 = ft_substr(result2, i + 2, ft_strlen(result2) - 2);
			i = 0;
		}
	}
	trimed_result = ft_strtrim(result2, " ");
	free(result2);
	free(result);
	return (trimed_result);
}

void	my_echo(char *arg)
{
	char	*str;
	int		option_check;
	char	*arg_new;

	arg_new = arg;
	option_check = check_echo_option(arg_new);
	str = remove_echo(arg_new, option_check);
	if (line_arg_count(str) == 0)
	{
		if (str[0] == '\0' && option_check == 0)
			write(1, "\n", 1);
		else if (str[0] == '\0' && option_check == 1)
			;
		else
			write(1, "echo: Multiline error\n", 24);
		return ;
	}
	exe_echo(str, option_check);
	free(str);
}
