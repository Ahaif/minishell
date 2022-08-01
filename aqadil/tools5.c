/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqadil <aqadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 01:27:26 by aqadil            #+#    #+#             */
/*   Updated: 2022/02/23 01:49:51 by aqadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	only_rd_fd(char *str)
{
	char	**spltd_str;
	char	*temp;
	int		i;
	int		f1;
	int		flag;

	i = 1;
	flag = 0;
	spltd_str = ft_split(str, '<');
	while (spltd_str[i])
	{
		temp = ft_strtrim(spltd_str[i], " ");
		if (cmd_contain(spltd_str[i], ' '))
		{
			temp = open_other_files(spltd_str[i]);
			flag++;
		}
		f1 = only_open(temp, '<');
		i++;
	}
	return (1);
}

int	input_output_redirect(char *str)
{
	char	**spltd_str;
	int		i;
	int		f1;

	spltd_str = ft_split(str, '<');
	i = 0;
	while (spltd_str[i])
	{
		if (cmd_contain(spltd_str[i], '>'))
			f1 = open_file_greater(spltd_str[i], i);
		else
			open_file_less(spltd_str[i], i);
		i++;
	}
	return (f1);
}

int	str_len(char const *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
