/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqadil <aqadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 10:06:04 by ahaifoul          #+#    #+#             */
/*   Updated: 2022/02/23 02:44:41 by aqadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*op_strjoin(char const *s1, char const *s2)
{
	char	*new;
	int		i;
	int		k;

	k = 0;
	i = 0;
	new = (char *)malloc(sizeof(char) * ((str_len(s1) + str_len(s2)) + 2));
	if (new == 0)
		return (0);
	while (s1[i])
	{
		new[i] = s1[i];
		i++;
	}
	new[i++] = '/';
	k = 0;
	while (s2[k])
		new[i++] = s2[k++];
	new[i] = '\0';
	return (new);
}

int	*check_str(char *str)
{
	int	*here_doc;

	here_doc = NULL;
	if (str_str(str, "<<"))
		here_doc = get_heredoc_content(str);
	return (here_doc);
}

void	check_acces(char *str)
{
	if (check_access(str))
	{
		perror("command not found: ");
		exit(0);
	}
}

void	handle_fd_error(int f1)
{
	if (f1 < 0)
	{
		perror("fg error");
		exit(0);
	}
}

int	get_fd_input(char *str)
{
	int		i;
	int		f1;
	char	**spltd_str;
	char	**temp;

	i = 0;
	spltd_str = ft_split(str, '<');
	while (spltd_str[i])
	{
		if (spltd_str[i + 1] == NULL)
		{
			if (cmd_contain(spltd_str[i], '>') || str_str(spltd_str[i], ">>"))
			{
				temp = ft_split(spltd_str[i], '>');
				f1 = open(ft_strtrim(temp[0], " "), O_RDWR, 0644);
			}
			else
				f1 = open(ft_strtrim(spltd_str[i], " "), O_RDWR, 0644);
			if (f1 < 0)
				handle_fd_error(f1);
		}
		i++;
	}
	return (f1);
}
