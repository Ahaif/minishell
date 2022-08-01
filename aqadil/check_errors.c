/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqadil <aqadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 14:14:02 by aqadil            #+#    #+#             */
/*   Updated: 2022/02/21 18:21:25 by aqadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	second_word_check(char *str)
{
	char	*trimed_str;

	trimed_str = ft_strtrim(str, " ");
	if (cmd_contain(trimed_str, ';') || trimed_str[0] == '|'
		|| (trimed_str[0] == '<' && trimed_str[1] == '<'))
	{
		printf("Syntax Error\n");
		free(trimed_str);
		g_env_var.status = 258;
		return (1);
	}
	free(trimed_str);
	return (0);
}

int	third_word_check(char *str)
{
	char	*trimed_str;
	int		i;

	i = 0;
	trimed_str = ft_strtrim(str, " ");
	while (trimed_str[i])
	{
		if (trimed_str[i - 1] == '>' && trimed_str[i] == '>'
			&& trimed_str[i + 1] == '>')
		{
			printf("Syntax Error\n");
			free(trimed_str);
			g_env_var.status = 258;
			return (1);
		}
		i++;
	}
	free(trimed_str);
	return (0);
}

int	forth_word_check(char *str)
{
	char	*trimed_str;
	int		i;

	i = -1;
	trimed_str = ft_strtrim(str, " ");
	while (trimed_str[++i])
	{
		if ((trimed_str[i - 1] == '>' && trimed_str[i] == ' '
				&& trimed_str[i + 1] == '>') || (trimed_str[i - 1] == '<'
				&& trimed_str[i] == ' '
				&& trimed_str[i + 1] == '<'))
		{
			printf("Syntax Error\n");
			free(trimed_str);
			g_env_var.status = 258;
			return (1);
		}
	}
	free(trimed_str);
	return (0);
}

int	fifth_word_check(char *str)
{
	char	*trimed_str;
	int		i;

	i = 0;
	trimed_str = ft_strtrim(str, " ");
	while (trimed_str[i])
	{
		if ((trimed_str[i - 1] == '<' && trimed_str[i] == ' '
				&& trimed_str[i + 1] == '>')
			|| (trimed_str[i - 1] == '>' && trimed_str[i] == ' '
				&& trimed_str[i + 1] == '<'))
		{
			printf("Syntax Error\n");
			free(trimed_str);
			g_env_var.status = 258;
			return (1);
		}
		i++;
	}
	free(trimed_str);
	return (0);
}

int	grammer_check(char *str)
{
	if (one_word_check(str))
		return (1);
	else if (second_word_check(str))
		return (1);
	else if (third_word_check(str))
		return (1);
	else if (forth_word_check(str))
		return (1);
	else if (fifth_word_check(str))
		return (1);
	return (0);
}
