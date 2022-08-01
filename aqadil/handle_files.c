/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqadil <aqadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 11:38:01 by ahaifoul          #+#    #+#             */
/*   Updated: 2022/02/23 02:43:44 by aqadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_files_gre(char *str)
{
	int	f1;

	f1 = 0;
	if (cmd_contain(str, '>') && (!cmd_contain(str, '<')))
		f1 = output_redirect(str);
	else if (cmd_contain(str, '<') && (!cmd_contain(str, '>')))
		f1 = input_redirect(str);
	return (f1);
}

int	only_open(char *str, char c)
{
	int	f1;

	f1 = 0;
	if (c == '<')
	{
		f1 = open(ft_strtrim(str, " "), O_RDWR, 0644);
		if (f1 < 0)
			handle_fd_error(f1);
	}
	else if (c == '>')
	{
		f1 = open(ft_strtrim(str, " "), O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (f1 < 0)
			handle_fd_error(f1);
	}
	return (f1);
}

int	only_open_append(char *str)
{
	int	f1;

	f1 = open(ft_strtrim(str, " "), O_CREAT | O_RDWR | O_APPEND, 0644);
	if (f1 < 0)
		handle_fd_error(f1);
	return (f1);
}

int	append_with_redirect(char **spltd_str, int i)
{
	int	f1;

	if (not_contain(spltd_str[i], '>') && not_contain(spltd_str[i], '<'))
		f1 = append_to_first_file(spltd_str[i]);
	else
		f1 = open_files_gre(spltd_str[i]);
	return (f1);
}

int	open_files_appe(char *str)
{
	int		i;
	char	**spltd_str;
	int		f1;

	spltd_str = ft_split22(str, ">>");
	i = 0;
	while (spltd_str[i])
	{
		if (i == 0)
		{
			if (not_contain(spltd_str[i], '>')
				|| not_contain(spltd_str[i], '<'))
				f1 = open_files(spltd_str[i]);
		}
		else
		{
			if (!cmd_contain(spltd_str[i], '>')
				&& (!cmd_contain(spltd_str[i], '<')))
				f1 = only_open_append(spltd_str[i]);
			else
				f1 = append_with_redirect(spltd_str, i);
		}
		i++;
	}
	return (f1);
}
