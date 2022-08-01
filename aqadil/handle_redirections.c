/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqadil <aqadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 15:36:07 by ahaifoul          #+#    #+#             */
/*   Updated: 2022/02/23 02:46:10 by aqadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	only_append_fd(char *str)
{
	char	**spltd_str;
	int		i;
	int		f1;
	char	*temp;

	i = 1;
	spltd_str = ft_split22(str, ">>");
	while (spltd_str[i])
	{
		if (spltd_str[i + 1] != NULL)
		{
			temp = ft_strtrim(spltd_str[i + 1], " ");
			if (cmd_contain(temp, ' '))
				temp = open_other_files(spltd_str[i]);
			f1 = only_open_append(temp);
		}
		else
			f1 = open_normal_file(spltd_str[i], 'a', ">>");
		i++;
	}
	return (f1);
}

int	open_files(char *str)
{
	int		f1;

	f1 = 0;
	if (cmd_contain(str, '>') && !cmd_contain(str, '<')
		&& !str_str(str, ">>") && !str_str(str, "<<"))
		f1 = truncat_mod_fd(str);
	else if (cmd_contain(str, '<') && !not_contain(str, '>')
		&& !str_str(str, ">>") && !str_str(str, "<<"))
		f1 = only_rd_fd(str);
	else if (cmd_contain(str, '<') && not_contain(str, '>')
		&& !str_str(str, ">>") && !str_str(str, "<<"))
		f1 = input_output_redirect(str);
	else if ((str_str(str, ">>") && !not_contain(str, '<')
			&& !not_contain(str, '>') && !str_str(str, "<<")))
		f1 = only_append_fd(str);
	else if (str_str(str, ">>") && (!str_str(str, "<<")
			&& (cmd_contain(str, '<') || cmd_contain(str, '>'))))
		f1 = open_files_appe(str);
	return (f1);
}

char	*get_cmd_app(char *str)
{
	char	**spltd_str;
	char	*cmd;

	spltd_str = ft_split22(str, ">>");
	if (cmd_contain(spltd_str[0], '>') || cmd_contain(spltd_str[0], '<'))
		cmd = get_special_cmd(spltd_str[0]);
	else
		cmd = spltd_str[0];
	return (cmd);
}

char	*get_cmd_io(char *str, char c)
{
	char	**spltd_str;
	char	*cmd;

	spltd_str = NULL;
	cmd = NULL;
	if (c == '>')
	{
		spltd_str = ft_split(str, '>');
		cmd = spltd_str[0];
	}
	else if (c == '<')
	{
		spltd_str = ft_split(str, '<');
		if (cmd_contain(spltd_str[0], '>'))
			cmd = get_special_cmd(spltd_str[0]);
		else
			cmd = spltd_str[0];
	}
	free(spltd_str);
	return (cmd);
}

int	not_contain(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != c && str[i + 1] == c && str[i + 2] != c)
			return (1);
		i++;
	}
	return (0);
}
