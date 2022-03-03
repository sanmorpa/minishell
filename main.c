/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samoreno <samoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 16:15:50 by samoreno          #+#    #+#             */
/*   Updated: 2022/03/02 16:46:59 by samoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_leaks(void)
{
	system("leaks -q minishell");
}

int	main(int argc, char **argv, char **envp)
{
	char	*read;
	int		exit;
	t_list	*env;

//	atexit(ft_leaks);
	exit = 0;
	(void)argc, (void)argv;
	env = ft_envlist(envp);
	if (!env)
		return (1);
	while (exit == 0)
	{
		read = readline("minishell$ ");
		if (read[0])
		{
			add_history(read);
			exit = ft_check(read, env);
		}
		else
			free(read);
	}
	rl_clear_history();
	return (0);
}
