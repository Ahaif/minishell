/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_helper3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqadil <aqadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 17:28:59 by aqadil            #+#    #+#             */
/*   Updated: 2022/02/14 19:10:52 by aqadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../aqadil/minishell.h"

int	is_valid_echo(char c)
{
	if (isalpha(c) || isdigit(c) || c == '?')
		return (1);
	return (0);
}

void	exe_echo(char *str, int option_check)
{
	int		pos;
	char	**args;
	int		i;

	i = 0;
	pos = 0;
	args = bring_args_in(str);
	while (i < arg_count(args))
	{
		pos = get_first_index(str, args[i], args, i);
		check_env_print(args[i], str, pos);
		i++;
	}
	if (option_check == 0)
		printf("\n");
	free_double_char(args);
}

int	handle_this_if(char *arg, int *i)
{
	int	start;
	int	end;
	int	check_print;

	check_print = 1;
	start = (*i);
	(*i)++;
	while (arg[(*i)] && is_valid_echo(arg[(*i)]) == 1
		&& arg[(*i)] != '$' && arg[(*i)] != ' ' && arg[(*i)] != '\''
		&& arg[(*i)] != '\"')
		(*i)++;
	end = (*i);
	check_print = print_env(start, end, arg);
	(*i) = (*i) - 1;
	return (check_print);
}

int	check_env_print(char *arg, char *str, int pos)
{
	int	i;
	int	check_print;

	check_print = 1;
	i = 0;
	while (arg[i])
	{
		if (arg[i] == '$' && check_quotes(str, pos, arg) == 1)
			check_print = handle_this_if(arg, &i);
		else
		{
			if ((i == 0) && (arg[0] == '\'' || arg[0] == '\"'))
				;
			else if ((i == ft_strlen(arg) - 1)
				&& (arg[ft_strlen(arg) - 1] == '\''
					|| arg[ft_strlen(arg) - 1] == '\"'))
					;
			else
				write(1, &arg[i], 1);
		}
		i++;
	}
	if (check_space(str, pos, arg) == 1 && check_print == 1)
		write(1, " ", 1);
	return (1);
}

int	args_quoted_h(char *str, int pos, char *arg)
{
	if (str[pos - 1] == '\"' || str[ft_strlen(arg) - 1] == '\"')
	{
		return (1);
	}
	return (0);
}
