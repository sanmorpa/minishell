/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samoreno <samoreno@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 12:35:56 by samoreno          #+#    #+#             */
/*   Updated: 2022/07/06 12:39:01 by samoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	change_env_pwd(char *oldpwd, t_comm *comm, char **command,
				t_list *env);

void	ft_cd(char **command, t_comm *comm, t_list *env)
{
	char	*oldpwd;

	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
		exitfree(command, comm, print_error(-1), env);
	else
	{
		if (chdir(command[1]) != 0)
			print_error(-1);
		else
		{
			if (change_env_pwd(oldpwd, comm, command, env) != 0)
			{
				free(oldpwd);
				exitfree(command, comm, print_error(-1), env);
			}
		}
		free(oldpwd);
	}
}

static int	change_env_pwd(char *oldpwd, t_comm *comm, char **command,
		t_list *env)
{
	char	*newpwd;
	char	*to_oldpwd;
	char	*to_pwd;

	newpwd = getcwd(NULL, 0);
	if (!newpwd)
		return (1);
	to_pwd = ft_strjoin("PWD=", newpwd);
	to_oldpwd = ft_strjoin("OLDPWD=", oldpwd);
	free(newpwd);
	if (!to_pwd || !to_oldpwd)
	{
		free(oldpwd);
		exitfree(command, comm, print_error(-1), env);
	}
	if (ft_replace(to_pwd, env) == 2 || ft_replace(to_oldpwd, env) == 2)
	{
		free(to_pwd);
		free(to_oldpwd);
		free(oldpwd);
		exitfree(command, comm, print_error(-1), env);
	}
	free(to_pwd);
	free(to_oldpwd);
	return (0);
}
