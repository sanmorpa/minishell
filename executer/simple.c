/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samoreno <samoreno@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 11:51:36 by samoreno          #+#    #+#             */
/*   Updated: 2022/07/06 12:44:39 by samoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_simple(t_comm *comm, t_list *env)
{
	char	**command;

	command = ft_split(comm->piped[0], ' ');
	if (!command)
		exitfree(command, comm, print_error(-1), env);
	if (ft_is_exact(command[0], "exit", ft_strlen(command[0])) == 0)
		ft_exit(command, comm, env);
	if (ft_is_exact(command[0], "pwd", ft_strlen(command[0])) == 0)
	{
		if (ft_pwd(count_split(command)) == 1)
			exitfree(command, comm, print_error(-1), env);
	}
	if (ft_is_exact(command[0], "env", ft_strlen(command[0])) == 0)
		ft_env(command, env);
	if (ft_is_exact(command[0], "export", ft_strlen(command[0])) == 0)
		ft_export(command, comm, env);
	if (ft_is_exact(command[0], "unset", ft_strlen(command[0])) == 0)
		ft_unset(command, comm, env);
	if (ft_is_exact(command[0], "echo", ft_strlen(command[0])) == 0)
		ft_echo(command, env);
	if (ft_is_exact(command[0], "cd", ft_strlen(command[0])) == 0)
		ft_cd(command, comm, env);
	ft_free(command, count_split(command));
}
