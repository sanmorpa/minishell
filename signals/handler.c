/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samoreno <samoreno@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 10:07:20 by samoreno          #+#    #+#             */
/*   Updated: 2022/07/08 12:59:04 by samoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_handler(int signum)
{
	(void)signum;
	g_flag = 1;
}

int	ctrld_handler(t_list *env)
{
	exitfree(NULL, NULL, 0, env);
	printf("Exit\n");
	return (0);
}

t_signal	fill_sigactions(void)
{
	t_signal	sigactions;

	sigactions.new_action.__sigaction_u.__sa_handler = sig_handler;
	sigactions.old_action.__sigaction_u.__sa_handler = sig_handler;
	if (tcgetattr(0, &sigactions.termios_old) != 0)
		exit(print_error(-1));
	sigactions.termios_new = sigactions.termios_old;
	sigactions.termios_new.c_lflag &= ~ECHOCTL;
	return (sigactions);
}

void	print_signal(t_signal *sigactions)
{
	tcsetattr(STDIN_FILENO, TCSANOW, &sigactions->termios_new);
	printf("/n");
	rl_on_new_line();
	tcsetattr(STDIN_FILENO, TCSANOW, &sigactions->termios_old);
}
