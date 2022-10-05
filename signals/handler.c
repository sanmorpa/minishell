/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josuna-t <josuna-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 10:07:20 by samoreno          #+#    #+#             */
/*   Updated: 2022/08/09 18:26:14 by josuna-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern t_signal	g_signal;

void	sig_handler_parent(int signum)
{
	if (signum == SIGINT)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		ft_putstr_fd("\n", 1);
		if (g_signal.cid1 > 0)
		{
			rl_redisplay();
			g_signal.s_flag = 3;
		}
		else
		{
			close(STDIN_FILENO);
			g_signal.s_flag = 2;
			g_signal.cid1 = 1;
		}
	}
	else if (signum == SIGQUIT)
	{
		rl_on_new_line();
		if (g_signal.cid1 < 0)
			g_signal.cid1 = 1;
	}
}

void	sig_handler_child(int signum)
{
	if (signum == SIGINT)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		ft_putstr_fd("^C\n", 1);
		g_signal.s_flag = SIGINT;
	}
	else if (signum == SIGQUIT)
	{
		write(1, "^\\Quit: 3\n", 10);
		g_signal.s_flag = SIGQUIT;
	}
}

int	ctrld_handler(t_list *env)
{
	if (g_signal.cid1 > 0)
	{
		printf("exit\n");
		ft_lstclear(&env, delcontent);
	}
	else
		g_signal.cid1 = 1;
	return (0);
}

void	fill_sigactions(void)
{
	g_signal.cid1 = 1;
	g_signal.parent_action.sa_handler = sig_handler_parent;
	g_signal.parent_action.sa_flags = SA_SIGINFO;
	sigemptyset(&g_signal.parent_action.sa_mask);
	g_signal.child_action.sa_handler = sig_handler_child;
	g_signal.child_action.sa_flags = SA_SIGINFO;
	g_signal.s_flag = 0;
	sigemptyset(&g_signal.child_action.sa_mask);
	g_signal.ctrl_slash.sa_handler = SIG_DFL;
	g_signal.ctrl_slash.sa_flags = SA_SIGINFO;
	sigemptyset(&g_signal.ctrl_slash.sa_mask);
	tcgetattr(STDIN_FILENO, &g_signal.termios_old);
	g_signal.termios_new = g_signal.termios_old;
	g_signal.termios_new.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &g_signal.termios_new);
}
