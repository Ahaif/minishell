/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqadil <aqadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 18:11:57 by aqadil            #+#    #+#             */
/*   Updated: 2022/02/22 20:58:25 by aqadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../aqadil/minishell.h"

void	ctrl_c_handler(int sig)
{
	if (sig)
		;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 1);
	rl_redisplay();
	g_env_var.status = 1;
}

void	ctrl_d_handler(int sig)
{
	if (sig == 1)
	{
		enable_signals_and_terminos();
		printf("exit\n");
		dec_bash_lvl();
		exit(0);
	}
	else
		return ;
}
