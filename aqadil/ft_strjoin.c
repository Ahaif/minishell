/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqadil <aqadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 20:47:29 by aqadil            #+#    #+#             */
/*   Updated: 2022/01/18 23:37:20 by aqadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_strlen(char const *s)
{
	size_t i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}

char *ft_strjoin(char const *s1, char *s2)
{
	int s1_size;
	int s2_size;
	char *ptr;
	int i;

	i = -1;
	if (!s1)
		return (s2);
	s1_size = ft_strlen(s1);
	s2_size = ft_strlen(s2);
	ptr = malloc((sizeof(char)) * ((s2_size + s1_size) + 1));
	if (ptr == NULL)
		return (NULL);
	while (s1[++i])
		ptr[i] = ((char *)s1)[i];
	s1_size = -1;
	while (s2[++s1_size])
		ptr[i++] = ((char *)s2)[s1_size];
	ptr[i] = '\0';
	return (ptr);
}