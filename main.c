/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samoreno <samoreno@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 09:57:02 by samoreno          #+#    #+#             */
/*   Updated: 2022/07/06 13:04:49 by samoreno         ###   ########.fr       */
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
	int		comm;
	t_list	*env;

	atexit(ft_leaks);
	(void)argc, (void)argv;
	comm = 0;
	env = envlist(envp);
	if (!env)
		return (print_error(-1));
	while (comm == 0)
	{
		read = readline("minishell$ ");
		if (read[0])
		{
			add_history(read);
			parser(read, env);
		}
		free(read);
	}
	ft_lstclear(&env, delcontent);
	rl_clear_history();
	return (0);
}
