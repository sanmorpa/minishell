/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samoreno <samoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 17:19:20 by samoreno          #+#    #+#             */
/*   Updated: 2022/03/03 11:16:24 by samoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_simple(char **split, t_list *env);

int	ft_check(char *str, t_list *env)
{
	char	**split;

	split = ft_split(str, '|');
	free(str);
	if (!split)
		return (1);
//	ft_exec(split);
	ft_simple(split, env);
	return (0);
}

static void	ft_simple(char **split, t_list *env)
{
	char	**command;

	command = ft_split(split[0], ' ');
	ft_free(split, 1);
	if (!command)
		ft_exitfree(NULL, 1, env);
	if (ft_is_exact(command[0], "exit", ft_strlen(command[0])) == 0)
		ft_exit(command, env);
	if (ft_is_exact(command[0], "pwd", ft_strlen(command[0])) == 0)
	{
		if (ft_pwd(ft_count_split(command)) == 1)
			ft_exitfree(command, 1, env);
	}
	if (ft_is_exact(command[0], "env", ft_strlen(command[0])) == 0)
		ft_env(command, env);
	if (ft_is_exact(command[0], "export", ft_strlen(command[0])) == 0)
		ft_export(command, env);
	if (ft_is_exact(command[0], "unset", ft_strlen(command[0])) == 0)
		ft_unset(command, env);
	if (ft_is_exact(command[0], "echo", ft_strlen(command[0])) == 0)
		ft_echo(command, env);
	ft_free(command, ft_count_split(command));

}
