/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josuna-t <josuna-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 12:35:56 by samoreno          #+#    #+#             */
/*   Updated: 2022/08/04 15:15:22 by josuna-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	change_env_pwd(char *oldpwd, t_list *env);
static int	check_pwd_again(void);

int	ft_cd(char **command, t_comm *comm, t_list *env)
{
	char	*oldpwd;

	oldpwd = getcwd(NULL, 0);
	if (chdir(command[1]) == 0)
	{
		if (comm->redirections->next == 0 && oldpwd)
		{
			if (change_env_pwd(oldpwd, env) != 0)
			{
				free(oldpwd);
				exitfree(comm, print_error(-1, "cd: error"), env);
			}
			free(oldpwd);
		}
		return (check_pwd_again());
	}
	else
	{
		if (oldpwd)
			free(oldpwd);
		print_error(-1, "cd: error");
		return (1);
	}
}

static int	check_pwd_again(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		print_error(-1, "cd: error");
		return (1);
	}
	else
		free(pwd);
	return (0);
}

static int	change_env_pwd(char *oldpwd, t_list *env)
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
		return (1);
	if (ft_replace(to_pwd, env) == 2 || ft_replace(to_oldpwd, env) == 2)
	{
		free(to_pwd);
		free(to_oldpwd);
		return (1);
	}
	free(to_pwd);
	free(to_oldpwd);
	return (0);
}
