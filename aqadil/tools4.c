/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqadil <aqadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 01:27:08 by aqadil            #+#    #+#             */
/*   Updated: 2022/02/23 02:48:10 by aqadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_special_cmd(char *str)
{
	char	**temp;
	char	**temp1;
	char	*cmd;

	if (cmd_contain(str, '>'))
		temp = ft_split(str, '>');
	else
		temp = ft_split(str, '<');
	if (cmd_contain(temp[0], '<'))
	{
		temp1 = ft_split(temp[0], '<');
		cmd = temp1[0];
		return (ft_strtrim(cmd, " "));
	}
	else if (cmd_contain(temp[0], '>'))
	{
		temp1 = ft_split(temp[0], '>');
		cmd = ft_strdup(temp1[0]);
	}
	else
		cmd = ft_strdup(temp[0]);
	return (ft_strtrim(cmd, " "));
}

int	open_file_rt(char **splt_str)
{
	int		i;
	int		f1;
	char	*temp;

	i = 0;
	while (splt_str[i])
	{
		temp = ft_strtrim(splt_str[i], " ");
		if (i == 0)
		{
			if (cmd_contain(temp, ' '))
				temp = open_other_files(splt_str[i]);
			f1 = only_open(temp, '<');
		}
		else
			f1 = open_normal_file(splt_str[i], '>', NULL);
		i++;
	}
	free(temp);
	return (f1);
}

int	open_file_greater(char *str, int index)
{
	char	**splt_str;
	int		i;
	int		f1;

	i = 0;
	splt_str = ft_split(str, '>');
	if (index == 0)
		f1 = escape_cmd_open_file(str);
	else
		f1 = open_file_rt(splt_str);
	return (f1);
}

void	open_file_less(char *str, int index)
{
	int	f1;

	if (index == 0)
		f1 = 0;
	else
		f1 = open_normal_file(str, '<', NULL);
}

int	truncat_mod_fd(char *str)
{
	char	**spltd_str;
	char	*temp;
	int		i;
	int		f1;

	i = 1;
	spltd_str = ft_split(str, '>');
	while (spltd_str[i])
	{
		temp = ft_strtrim(spltd_str[i], " ");
		if (cmd_contain(spltd_str[i], ' '))
			temp = open_other_files(spltd_str[i]);
		f1 = only_open(temp, '>');
		i++;
	}
	return (f1);
}
