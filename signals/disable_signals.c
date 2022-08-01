/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disable_signals.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqadil <aqadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 18:12:02 by aqadil            #+#    #+#             */
/*   Updated: 2022/02/12 01:46:04 by aqadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../aqadil/minishell.h"

void	disable_signals_terminos(void)
{
	mini_enable_signals_and_terminos();
	signal(SIGINT, ctrl_c_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	mini_enable_child_termios_s(void)
{
	enable_child_termios_s();
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
}

void	enable_child_termios_s(void)
{
	struct termios	term;

	if (isatty(STDIN_FILENO) == 0)
		printf("standard input is not a terminal device");
	if (tcgetattr(STDIN_FILENO, &term) < 0)
		printf("tcgetattr error");
	term.c_lflag = ECHO;
	term.c_lflag |= ISIG;
	term.c_lflag |= ECHOK;
	term.c_lflag |= ECHOE;
	term.c_lflag |= ECHOKE;
	term.c_lflag |= PENDIN;
	term.c_lflag |= ICANON;
	term.c_lflag |= IEXTEN;
	term.c_lflag |= ECHOCTL;
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &term) < 0)
		printf("tcsetattr error");
}

void	disable_signals(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}
