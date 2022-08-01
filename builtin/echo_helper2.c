/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_helper2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqadil <aqadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 16:34:53 by aqadil            #+#    #+#             */
/*   Updated: 2022/02/22 21:05:47 by aqadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../aqadil/minishell.h"

int	skip_those(char *str, int i, char **args)
{
	int	k;
	int	index;
	int	count;

	k = 0;
	count = arg_count(args);
	index = 0;
	while (k < i)
	{
		index = index + ft_strlen(args[k]);
		while (str[index] == ' ')
			index++;
		k++;
	}
	while (str[index] == ' ')
		index++;
	return (index);
}

int	get_first_index(char *str, char *arg, char **args, int index)
{
	int	i;
	int	j;

	(void)arg;
	i = 0;
	j = 0;
	i = skip_those(str, index, args);
	return (i);
}

int	check_space(char *str, int pos, char *arg)
{
	int	so;

	so = pos + ft_strlen(arg);
	if (str[so] == ' ')
		return (1);
	return (0);
}

int	check_forward_s(char *str, int pos)
{
	int	i;
	int	single_q;
	int	double_q;

	i = 0;
	single_q = 0;
	double_q = 0;
	while (str[pos])
	{
		if (str[pos] == '\'')
		{
			double_q = 0;
			single_q++;
		}
		if (str[pos] == '\"')
		{
			return (1);
		}
		pos++;
	}
	if (double_q == 0)
		return (0);
	return (1);
}

int	check_quotes(char *str, int index, char *arg)
{
	int	i;
	int	single_q;
	int	double_q;

	i = 0;
	single_q = 0;
	double_q = 0;
	if (str[0] == '\"' && str[ft_strlen(str) - 1] == '\"')
		return (1);
	else if (check_surrounded(arg, index) == 1)
		return (1);
	return (0);
}
