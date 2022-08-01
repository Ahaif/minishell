/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqadil <aqadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 02:17:13 by aqadil            #+#    #+#             */
/*   Updated: 2022/02/23 02:46:22 by aqadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./aqadil/minishell.h"

static int	count_word(const char *s, char *set)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == set[0] && s[i + 1] == set[1])
		{
			count++;
		}
		i++;
	}
	count = count + 1;
	return (count);
}

static char	*create_word(const char *s, int start, int end)
{
	char	*word;
	int		i;
	int		word_len;

	i = 0;
	word_len = end - start;
	word = (char *)malloc((word_len * sizeof(char )) + 1);
	while (start < end)
		word[i++] = s[start++];
	word[i] = '\0';
	return (word);
}

static int	fill_the_splited_array(char **str, const char *s, char *set)
{
	t_vars	var;

	new_var_init(&var);
	while (s[var.i])
	{
		if ((s[var.i] != set[0] && s[var.i + 1] != set[1])
			|| (s[var.i] != set[0] && s[var.i + 1] == set[1]
				&& s[var.i + 2] != set[1]))
		{
			var.start = var.i;
			while ((s[var.i]) && ((s[var.i] != set[0] && s[var.i + 1] != set[1])
					|| (s[var.i] != set[0] && s[var.i + 1] == set[1]
						&& s[var.i + 2] != set[1])
					|| (s[var.i] == set[0] && s[var.i + 1] != set[1])))
				if (var.i++ && (s[var.i + 1] != set[0]
						&& s[var.i + 2] == set[1]))
					var.i++;
			var.end = var.i;
			str[var.k++] = create_word(s, var.start, var.end);
		}
		else
			var.i++;
	}
	str[var.k] = 0;
	return (1);
}

char	**ft_split22(char *s, char *set)
{
	char	**str;
	int		checker;

	checker = 1;
	if (!s)
		return (NULL);
	str = (char **)malloc(((count_word(s, set) + 1) * (sizeof(char *))));
	if (str == NULL)
		return (NULL);
	checker = fill_the_splited_array(str, s, set);
	if (checker == 0)
		return (NULL);
	return (str);
}
