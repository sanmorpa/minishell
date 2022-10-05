/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samoreno <samoreno@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 11:17:39 by samoreno          #+#    #+#             */
/*   Updated: 2022/08/04 13:19:17 by samoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int		addq(t_list *env, char *to_add);
static t_list	*fill_basics(int length, char *pwd);

static void	fill_envlist(char **envp, t_list *env)
{
	int		i;
	t_dict	*entry;

	i = 1;
	while (envp[i])
	{
		entry = dict(envp[i++]);
		if (!entry->key)
		{
			ft_lstclear(&env, delcontent);
			exit(print_error(-1, "Error"));
		}
		ft_lstadd_back(&env, ft_lstnew((void *)entry));
	}
	if (addq(env, "?=0") == 1)
	{
		ft_lstclear(&env, delcontent);
		exit(print_error(-1, "Error"));
	}
}

t_list	*envlist(char **envp)
{
	t_list	*env;
	t_dict	*entry;
	char	*pwd;

	if (!envp || !envp[0])
	{
		pwd = getcwd(NULL, 0);
		if (!pwd)
			return (NULL);
		env = fill_basics(ft_strlen(pwd) + 5, pwd);
		free(pwd);
		return (env);
	}
	entry = dict(envp[0]);
	if (!entry->key)
		return (NULL);
	env = ft_lstnew((void *)entry);
	if (!env)
	{
		delcontent((void *)entry);
		return (NULL);
	}
	fill_envlist(envp, env);
	return (env);
}

static t_list	*fill_basics(int length, char *pwd)
{
	t_list	*env;
	t_dict	*e;
	char	*save_pwd;

	save_pwd = malloc(sizeof(char) * length);
	if (!save_pwd)
		exit(print_error(-1, "Error"));
	ft_strlcpy(save_pwd, "PWD=", ft_strlen("PWD=") + 1);
	ft_strlcat(save_pwd, pwd, ft_strlen(save_pwd) + ft_strlen(pwd) + 1);
	e = dict(save_pwd);
	free(save_pwd);
	if (!e)
		exit(print_error(-1, "Error"));
	env = ft_lstnew((void *)e);
	if (!env)
	{
		delcontent((void *)e);
		exit(print_error(-1, "Error"));
	}
	if (addq(env, "OLDPWD") == 1 || addq(env, "SHLVL=1") == 1
		|| addq(env, "_=/usr/bin/env") == 1 || addq(env, "?=0") == 1)
		exit(print_error(-1, "Error"));
	return (env);
}

static int	addq(t_list *env, char *to_add)
{
	t_dict	*entry;

	entry = dict(to_add);
	if (!entry->key)
	{
		ft_lstclear(&env, delcontent);
		return (1);
	}
	ft_lstadd_back(&env, ft_lstnew((void *)entry));
	return (0);
}

t_dict	*dict(char *envp)
{
	t_dict	*entry;
	size_t	e;

	e = is_equal(envp);
	entry = malloc(sizeof(t_dict));
	entry->key = malloc(sizeof(char) * (e + 1));
	if (e == ft_strlen(envp) && envp[e - 1] != '=')
		entry->value = NULL;
	else
	{
		if (ft_strchr(envp, '$'))
			entry->value = malloc(sizeof(char) * (ft_strlen(envp) - e + 3));
		else
			entry->value = malloc(sizeof(char) * (ft_strlen(envp) - e + 1));
	}
	if (!entry || !entry->key || (!entry->value
			&& (e != ft_strlen(envp) || envp[e - 1] == '=')))
	{
		delcontent((void *)entry);
		entry->key = NULL;
		return (NULL);
	}
	ft_strlcpy(entry->key, envp, e + 1);
	fill_value_dict(e, entry, envp);
	return (entry);
}
