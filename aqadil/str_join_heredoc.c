/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_join_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqadil <aqadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 17:53:40 by ahaifoul          #+#    #+#             */
/*   Updated: 2022/02/23 00:49:25 by aqadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*str_join_heredoc(char *s1, char *s2)
{
	char	*new;
	int		i;
	int		k;

	k = 0;
	i = 0;
	if (!s1)
		return (s2);
	new = (char *)malloc(sizeof(char) * ((str_len(s1) + str_len(s2)) + 4));
	if (new == 0)
		return (0);
	while (s1[i])
	{
		new[i] = s1[i];
		i++;
	}
	if (new[i - 1] != '\n')
		new[i] = '\n';
	i++;
	while (s2[k])
		new[i++] = s2[k++];
	new[i] = '\0';
	return (new);
}

char	*get_delimetr(char *str)
{
	char	*del;
	char	**spltd_str;

	if (cmd_contain(str, ' '))
	{
		spltd_str = ft_split(str, ' ');
		del = ft_strtrim(spltd_str[0], " ");
	}
	else if (cmd_contain(str, '>')
		|| cmd_contain(str, '<') || str_str(str, ">>"))
		del = get_cmmd(str);
	else
		del = ft_strtrim(str, " ");
	return (del);
}
