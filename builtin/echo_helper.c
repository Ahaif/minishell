/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqadil <aqadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 15:56:49 by aqadil            #+#    #+#             */
/*   Updated: 2022/02/19 15:26:06 by aqadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../aqadil/minishell.h"

void	echo_helper_1(char *result)
{
	int	i;

	if (result[1] == '0')
		write(1, "bash", 4);
	i = 2;
	while (result[i])
		write(1, &result[i++], 1);
}

void	echo_helper_2(char *result)
{
	int	i;

	ft_putnbr(g_env_var.status);
	i = 2;
	while (result[i])
		write(1, &result[i++], 1);
}

void	echo_helpr_3(char *result)
{
	while (*result)
		write(1, result++, 1);
}

int	echo_helper_5(char *result)
{
	char	*result2;

	result2 = remove_dollar(result);
	if (get_my_env(result2) != NULL)
	{
		result2 = get_my_env(result2);
		write(1, result2, ft_strlen(result2));
		free(result2);
	}
	else
		return (0);
	return (1);
}

int	check_self(char *arg)
{
	if (arg[0] == '\"' && arg[ft_strlen(arg) - 1] == '\"')
		return (1);
	return (0);
}
