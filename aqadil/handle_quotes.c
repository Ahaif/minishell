/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqadil <aqadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 15:35:30 by aqadil            #+#    #+#             */
/*   Updated: 2022/02/19 15:39:50 by aqadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_same_type_quotes(char *str)
{
	int	quote;
	int	i;

	i = 0;
	quote = 10;
	while (str[i])
	{
		if (str[i] == '\"')
		{
			if (quote == 0)
				return (0);
			quote = 1;
		}
		if (str[i] == '\'')
		{
			if (quote == 1)
				return (0);
			quote = 0;
		}
		i++;
	}
	return (1);
}

char	*r_helper(void)
{
	printf("MiniShell: multiline Error\n");
	return (NULL);
}

char	*remove_quotes_if_exists(char *str)
{
	int		i;
	char	*result;
	int		j;

	if (cmd_contain(str, '\"') == 0 && cmd_contain(str, '\'') == 0)
		return (str);
	if (line_arg_count(str) == 0)
		return (r_helper());
	if (check_same_type_quotes(str) == 1)
	{
		result = malloc(count_no_quotes_str(str) + 1);
		if (result == NULL)
			return (NULL);
		i = -1;
		j = 0;
		while (str[++i])
			if (str[i] != '\'' && str[i] != '\"')
				result[j++] = str[i];
		result[j] = 0;
	}
	else
		result = remove_first_last_quotes(str);
	free(str);
	return (result);
}

char	*remove_first_last_quotes(char *str)
{
	char	*result;
	int		quotes;

	if (str[0] == '\'')
	{
		result = ft_strtrim(str, "\'");
		quotes = 1;
	}
	else
	{
		result = ft_strtrim(str, "\"");
		quotes = 2;
	}
	return (result);
}

char	*handle_quotes(char *str)
{
	if (line_arg_count(str) == 0)
	{
		printf("Minishell: Multiline Error\n");
		return (NULL);
	}
	if (str[0] == '\"' && str[ft_strlen(str) - 1] == '\"')
		str = ft_strtrim(str, "\"");
	else if (str[0] == '\'' && str[ft_strlen(str) - 1] == '\''
		&& cmd_contain(str, '$') == 0)
	{
		str = ft_strtrim(str, "\'");
	}
	return (str);
}
