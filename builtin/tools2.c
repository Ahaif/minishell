/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqadil <aqadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 17:55:31 by aqadil            #+#    #+#             */
/*   Updated: 2022/02/23 02:20:34 by aqadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../aqadil/minishell.h"

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putnbr(int nb)
{
	if (nb == -2147483648)
	{
		ft_putchar('-');
		ft_putchar('2');
		nb = 147483648;
	}
	if (nb < 0)
	{
		ft_putchar('-');
		nb = -nb;
	}
	if (nb <= 9)
	{
		ft_putchar(nb + 48);
	}
	else
	{
		ft_putnbr(nb / 10);
		ft_putnbr(nb % 10);
	}
}

int	line_arg_count_h_2(char *str, int i, int *count)
{
	while (str[i + 1] != '\'' && str[i + 1] != '\"'
		&& str[i + 1] != ' ' && str[i + 1])
		i++;
	(*count)++;
	return (i);
}

int	line_arg_count_h_3(char *str, int i, int *count)
{
	while (str[i + 1] != '\"' && str[i + 1] != '\0')
		i++;
	if (str[i + 1] != '\"')
		return (0);
	i++;
	(*count)++;
	return (i);
}

void	var_init(t_vars *vars)
{
	vars->i = 0;
	vars->single_quote = 0;
	vars->double_quote = 0;
	vars->count = 0;
	vars->j = 0;
	vars->start = -1;
	vars->end = -1;
	vars->pipe_counter = 0;
}
