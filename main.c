/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samoreno <samoreno@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 09:57:02 by samoreno          #+#    #+#             */
/*   Updated: 2022/07/08 13:21:56 by samoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_flag;

void	ft_leaks(void)
{
	system("leaks -q minishell");
}

int	main(int argc, char **argv, char **envp)
{
	char		*read;
	t_list		*env;
	t_signal	sigactions;

	atexit(ft_leaks);
	sigactions = fill_sigactions();
	sigaction(SIGINT, &sigactions.new_action, &sigactions.old_action);
	(void)argc, (void)argv;
	env = envlist(envp);
	if (!env)
		return (print_error(-1));
	while (1)
	{
		if (g_flag == 1)
		{
			print_signal(&sigactions);
		}
		read = readline("minishell$ ");
		if (!read)
			return (ctrld_handler(env));
		if (read[0])
		{
			add_history(read);
			parser(read, env);
		}
		free(read);
	}
	return (0);
}
