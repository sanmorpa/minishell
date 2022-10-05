/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samoreno <samoreno@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 11:51:36 by samoreno          #+#    #+#             */
/*   Updated: 2022/09/05 12:15:48 by samoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern t_signal	g_signal;

void	check_status(int status, t_list **env, t_comm *comm)
{
	char	*result;
	char	*replace;

	if (WIFEXITED(status))
		result = ft_itoa(WEXITSTATUS(status));
	else if (WTERMSIG(status))
	{
		if (status == 2)
			result = ft_itoa(130);
		else if (status == 3)
			result = ft_itoa(131);
		else
			result = ft_itoa(status);
	}
	else
		result = ft_itoa(status);
	replace = ft_strjoin("?=", result);
	if (replace == 0)
		exitfree(comm, -1, *env);
	free(result);
	ft_replace(replace, *env);
	free(replace);
}

void	ft_exec(t_comm comm, t_list **env)
{
	int		*cids;
	int		pipefd[4];

	pipefd[0] = -1;
	pipefd[3] = 0;
	if (g_signal.s_flag == 2)
	{
		check_status(1, env, &comm);
		g_signal.s_flag = 0;
		return ;
	}
	cids = malloc(sizeof(int *) * ft_lstsize(comm.redirections));
	while (comm.redirections != 0)
	{
		pipefd[3] = f_redirections(comm, env, cids, pipefd);
		comm.redirections = comm.redirections->next;
	}
	sigaction(SIGINT, &g_signal.child_action, NULL);
	sigaction(SIGQUIT, &g_signal.child_action, NULL);
	pipefd[3] = waitallchilds(cids, pipefd[3]);
	sigaction(SIGINT, &g_signal.parent_action, NULL);
	sigaction(SIGQUIT, &g_signal.parent_action, NULL);
	check_status(pipefd[3], env, &comm);
	free(cids);
}

void	ft_exec2(char **commands, t_list **env)
{
	char	**envs;
	char	*pathcommand;

	envs = ft_lsttostring(*env);
	pathcommand = checkpath(commands, envs);
	if (commands[0][0] == '.' || pathcommand == 0)
		execve(commands[0], commands, envs);
	else
		execve(pathcommand, commands, envs);
	ft_free(envs, ft_lstsize(*env));
	if (commands[0][0] != '.' && commands[0][0] != '/' && pathcommand == 0)
	{
		write(2, commands[0], ft_strlen(commands[0]));
		write(2, ": command not found\n", 20);
	}
	else
		perror(commands[0]);
	if (access(commands[0], F_OK) == 0 && access(commands[0], X_OK))
		exit(126);
	exit(127);
}

void	ft_simple(t_element *command, t_list **env, t_comm *comm)
{
	if (command->command[0] != 0 && command->command[0][0])
	{
		if (ft_is_exact(command->command[0], "pwd", 3, 1) == 0)
			exit(ft_pwd(env, comm));
		else if (ft_is_exact(command->command[0], "env", 3, 1) == 0)
			exit(ft_env(command->command, *env));
		else if (ft_is_exact(command->command[0], "export", 6, 1) == 0)
			exit(ft_export(command->command, comm, *env,
					count_split(command->command) - 1));
		else if (ft_is_exact(command->command[0], "unset", 5, 1) == 0)
			exit(ft_unset(command->command, env));
		else if (ft_is_exact(command->command[0], "echo", 4, 1) == 0)
			ft_echo(command->command, *env);
		else if (ft_is_exact(command->command[0], "exit", 4, 1) == 0)
			exit(ft_exit(command->command, comm, *env, 1));
		else if (ft_is_exact(command->command[0], "cd", 2, 1) == 0)
			exit(ft_cd(command->command, comm, *env));
		ft_exec2(command->command, env);
	}
	else if (!command->command[0])
		exit(0);
	write(2, "command not found\n", 18);
	exit(127);
}
