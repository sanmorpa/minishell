/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josuna-t <josuna-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 16:07:20 by josuna-t          #+#    #+#             */
/*   Updated: 2022/08/09 18:04:36 by josuna-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern t_signal	g_signal;

int	waitallchilds(int *cids, int count)
{
	int	index;
	int	returni;

	index = 0;
	while (index < count)
	{
		waitpid(cids[index++], &returni, 0);
		if (g_signal.s_flag != 0)
		{
			returni = g_signal.s_flag;
			g_signal.s_flag = 0;
		}
	}
	waitpid(-1, 0, 0);
	return (returni);
}

void	ft_dup(t_list *commands, int count, int *pipefd)
{
	if (count == 0 && commands->next != 0)
	{
		close(pipefd[0]);
		dup2(pipefd[1], 1);
		close(pipefd[1]);
	}
	else if (count != 0 && commands->next == 0)
	{
		close(pipefd[0]);
		close(pipefd[1]);
		dup2(pipefd[2], 0);
		close(pipefd[2]);
	}
	else if (count != 0 && commands->next != 0)
	{
		close(pipefd[0]);
		dup2(pipefd[1], 1);
		close(pipefd[1]);
		dup2(pipefd[2], 0);
		close(pipefd[2]);
	}
}

int	f_redirections(t_comm comm, t_list **env, int *cids, int *pipefd)
{
	pipe(pipefd);
	cids[pipefd[3]] = fork();
	if (cids[pipefd[3]] == 0)
	{
		sigaction(SIGINT, &g_signal.ctrl_slash, NULL);
		sigaction(SIGQUIT, &g_signal.ctrl_slash, NULL);
		ft_dup(comm.redirections, pipefd[3], pipefd);
		if (ft_redirect((t_element *)comm.redirections->content) != 0)
			exitfree(&comm, 1, *env);
		ft_simple((t_element *)comm.redirections->content, env, &comm);
	}
	else if (g_signal.cid1 == -1)
		exitfree(&comm, print_error(-1, "Fork error: "), *env);
	close(pipefd[1]);
	if (pipefd[3]++ > 0)
		close (pipefd[2]);
	pipefd[2] = pipefd[0];
	return (pipefd[3]);
}
