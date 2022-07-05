/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samoreno <samoreno@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 11:51:36 by samoreno          #+#    #+#             */
/*   Updated: 2022/07/05 14:23:48 by samoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_simple(t_comm *comm, t_list *env)
{
	char	**command;

	command = ft_split(comm->piped[0], ' ');
	ft_free(comm->piped, 1);
	if (!command)
	{
		free(comm->og);
		free(comm->parsed);
		free(comm->piped);
		exit(print_error(-1));
	}
	if (ft_is_exact(command[0], "exit", ft_strlen(command[0])) == 0)
		ft_exit(command, env);
	if (ft_is_exact(command[0], "pwd", ft_strlen(command[0])) == 0)
	{
		if (ft_pwd(count_split(command)) == 1)
			exitfree(command, 1, env);
	}
	if (ft_is_exact(command[0], "env", ft_strlen(command[0])) == 0)
		ft_env(command, env);
	if (ft_is_exact(command[0], "export", ft_strlen(command[0])) == 0)
		ft_export(command, env);
	if (ft_is_exact(command[0], "unset", ft_strlen(command[0])) == 0)
		ft_unset(command, env);
	if (ft_is_exact(command[0], "echo", ft_strlen(command[0])) == 0)
		ft_echo(command, env);
	if (ft_is_exact(command[0], "cd", ft_strlen(command[0])) == 0)
		ft_cd(command, env);
	ft_free(command, count_split(command));
}
