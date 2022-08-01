/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_str.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqadil <aqadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 15:35:48 by ahaifoul          #+#    #+#             */
/*   Updated: 2022/02/23 01:51:55 by aqadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*str_str(char *str, char *to_find)
{
	int	i;
	int	j;

	i = 0;
	if (!(*to_find))
	{
		return (str);
	}
	while (str[i] != '\0')
	{
		j = 0;
		if (str[i] == to_find[j])
		{
			while (to_find[j] != '\0' && str[i + j] == to_find[j])
			{
				j++;
			}
			if (to_find[j] == '\0')
				return (&str[i]);
		}
		i++;
	}
	return (0);
}
