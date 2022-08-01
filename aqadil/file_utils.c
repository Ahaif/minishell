/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqadil <aqadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 18:31:14 by ahaifoul          #+#    #+#             */
/*   Updated: 2022/02/23 01:53:13 by aqadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_file_gr(char *str, int index)
{
	char	**temp;
	int		i;
	int		f1;
	int		f2;

	i = 0;
	temp = ft_split(str, '>');
	while (temp[i])
	{
		if (index == 0)
		{
			f1 = open(ft_strtrim(temp[0], " "),
					O_CREAT | O_RDWR | O_APPEND, 0644);
			if (f1 < 0)
				handle_fd_error(f1);
		}
		else
			f2 = only_open(temp[i], '>');
		i++;
	}
	return (f1);
}

int	special_open_for_append(char *str)
{
	char	**spltd_str;
	int		i;
	int		f1;

	i = 0;
	spltd_str = ft_split(str, '>');
	while (spltd_str[i])
	{
		if (i == 0)
			f1 = only_open_append(spltd_str[i]);
		else
			f1 = only_open(spltd_str[i], '>');
		i++;
	}
	return (f1);
}

int	append_to_first_file(char *str)
{
	char	**spltd_str;
	int		i;
	int		f1;
	int		f2;

	i = 0;
	spltd_str = ft_split(str, '<');
	while (spltd_str[i])
	{
		if (cmd_contain(spltd_str[i], '>'))
			f1 = special_open_for_append(spltd_str[i]);
		else
		{
			if (i == 0)
				f2 = only_open_append(spltd_str[0]);
			else
				f2 = only_open(spltd_str[i], '<');
		}
		i++;
	}
	return (f1);
}

int	output_redirect(char *str)
{
	char	**spltd_str;
	int		i;
	int		f1;
	int		f2;

	i = 0;
	spltd_str = ft_split(str, '>');
	while (spltd_str[i])
	{
		if (i == 0)
		{
			f2 = open(ft_strtrim(spltd_str[i], " "), O_CREAT | O_RDWR, 0644);
			if (f2 < 0)
				handle_fd_error(f2);
		}
		else
			f1 = only_open(spltd_str[i], '>');
		i++;
	}
	return (f1);
}

int	input_redirect(char *str)
{
	char	**spltd_str;
	int		i;
	int		f1;
	int		f2;

	i = 0;
	spltd_str = ft_split(str, '<');
	i = 0;
	while (spltd_str[i])
	{
		if (i == 0)
			f1 = only_open_append(spltd_str[i]);
		else
			f2 = only_open(spltd_str[i], '<');
		i++;
	}
	return (f1);
}
