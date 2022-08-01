/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_tools4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqadil <aqadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 22:26:52 by aqadil            #+#    #+#             */
/*   Updated: 2022/02/22 21:06:48 by aqadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../aqadil/minishell.h"

char	*parse_var(char *var, char *value)
{
	char	*new_var;

	new_var = var;
	if (ft_isdigit(var[0]))
	{
		printf("export: `%s=%s': not a valid identifier\n", var, value);
		return (NULL);
	}
	else if (check_exported_var(var) == 0)
	{
		if (value != '\0')
			printf("export: `%s=%s': not a valid identifier\n", var, value);
		else
			printf("export: `%s': not a valid identifier\n", var);
		return (NULL);
	}
	return (new_var);
}

int	check_exported_var(char *str)
{
	int	i;

	i = 1;
	while (str[i])
	{
		if (((ft_isalnum(str[i]) == 0) && str[i] != '_'))
			return (0);
		i++;
	}
	return (1);
}

char	*get_export_value(char *str)
{
	int		i;
	char	*value;
	int		start;
	int		end;

	i = 0;
	start = 0;
	while (str[i])
	{
		if (str[i] == '=')
		{
			start = i + 1;
			break ;
		}
		i++;
	}
	end = ft_strlen(str);
	value = ft_substr(str, start, end - start);
	return (value);
}

char	*get_export_var(char *str)
{
	int		i;
	char	*var;
	int		start;
	int		end;

	end = 0;
	i = 0;
	while (str[i])
	{
		if (i == 0)
			start = i;
		if (str[i] == '=')
		{
			end = i;
			break ;
		}
		i++;
	}
	var = ft_substr(str, start, end - start);
	return (var);
}

int	okey(void)
{
	printf("export: not a valid identifier\n");
	return (0);
}
