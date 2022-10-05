/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josuna-t <josuna-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 09:57:02 by samoreno          #+#    #+#             */
/*   Updated: 2022/08/09 18:28:28 by josuna-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_signal	g_signal;

void	check_flag(t_list *env)
{
	if (g_signal.s_flag == 3)
	{
		check_status(1, &env, NULL);
		g_signal.s_flag = 0;
	}
}

int	main(int argc, char **argv, char **envp)
{
	char		*read;
	t_list		*env;

	(void)argc, (void)argv;
	fill_sigactions();
	sigaction(SIGINT, &g_signal.parent_action, NULL);
	sigaction(SIGQUIT, &g_signal.parent_action, NULL);
	env = envlist(envp);
	if (!env)
		return (print_error(-1, "Error"));
	while (1)
	{
		read = readline("minishell$ ");
		if (!read)
			return (ctrld_handler(env));
		check_flag(env);
		if (read[0])
		{
			add_history(read);
			parser(read, &env);
		}
		free(read);
	}
	return (0);
}
