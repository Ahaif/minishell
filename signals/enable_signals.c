/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enable_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqadil <aqadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 22:03:54 by aqadil            #+#    #+#             */
/*   Updated: 2022/02/19 21:44:59 by aqadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../aqadil/minishell.h"

void	mini_enable_signals_and_terminos(void)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag = ECHO;
	term.c_lflag |= ISIG;
	term.c_lflag |= ECHOK;
	term.c_lflag |= ECHOE;
	term.c_lflag |= ECHOKE;
	term.c_lflag |= PENDIN;
	term.c_lflag |= ICANON;
	term.c_lflag |= IEXTEN;
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &term);
}

void	enable_signals_and_terminos(void)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag = 536872399;
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &term);
}

void	handle_mini_exe(void)
{
	enable_signals_and_terminos();
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
