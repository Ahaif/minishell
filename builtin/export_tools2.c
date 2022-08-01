/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_tools2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqadil <aqadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 22:26:54 by aqadil            #+#    #+#             */
/*   Updated: 2022/02/14 20:01:52 by aqadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../aqadil/minishell.h"

char	*remove_export_word(char *line)
{
	char	*result;
	int		i;
	int		j;
	char	*trimed_result;

	i = 6;
	j = 0;
	line = ft_strtrim(line, " ");
	result = malloc(ft_strlen(line) - 6);
	if (result == NULL)
		return (NULL);
	while (line[i])
	{
		result[j] = line[i];
		j++;
		i++;
	}
	trimed_result = ft_strtrim(result, " ");
	free(result);
	if (trimed_result[0] == '=')
	{
		printf("export: %s: not a valid identifier\n", trimed_result);
		return (NULL);
	}
	return (trimed_result);
}

int	var_contain_space(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ' ')
			return (1);
		i++;
	}
	return (0);
}

char	*remove_all_quotes(char *str)
{
	int		i;
	int		j;
	char	*result;

	j = 0;
	i = 0;
	if (str == NULL)
		return (NULL);
	if (line_arg_count(str) == 0)
	{
		printf("export : Multiline Error\n");
		return (NULL);
	}
	else
	{
		result = malloc(count_without_quotes(str) + 1);
		while (str[i])
		{
			if (str[i] != '\'' && str[i] != '\"')
				result[j++] = str[i];
			i++;
		}
		result[j] = 0;
	}
	return (result);
}

int	count_without_quotes(char *str)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] != '\"' && str[i] != '\'')
			count++;
		i++;
	}
	return (count);
}

char	**get_my_env_copy(char *var, char *value)
{
	int		i;
	int		count;
	char	**result;
	char	*join;

	count = 0;
	i = 0;
	count = count_my_env();
	result = malloc((count + 2) * sizeof(char *));
	if (result == NULL)
		return (NULL);
	join = ft_strjoin(var, "=");
	join = ft_strjoin(join, value);
	while (g_env_var.env[i])
	{
		result[i] = ft_strdup(g_env_var.env[i]);
		i++;
	}
	result[i] = join;
	result[i + 1] = 0;
	return (result);
}
