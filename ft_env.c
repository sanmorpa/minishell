/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samoreno <samoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 16:06:55 by samoreno          #+#    #+#             */
/*   Updated: 2022/03/01 12:24:15 by samoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*ft_envlist(char **envp)
{
	t_list	*env;
	t_list	*add;
	t_dict	*entry;
	int		i;

	i = 0;
	entry = ft_dict(envp[i++]);
	if (!entry->key)
		return (NULL);
	env = ft_lstnew((void *)entry);
	while (envp[i])
	{
		entry = ft_dict(envp[i++]);
		if (!entry->key)
		{
			ft_lstclear(&env, ft_delcontent);
			return (NULL);
		}
		add = ft_lstnew((void *)entry);
		ft_lstadd_back(&env, add);
	}
	return (env);
}

t_dict	*ft_dict(char *envp)
{
	t_dict	*entry;
	int		e;

	e = ft_isequal(envp);
	entry = (t_dict *)malloc(sizeof(t_dict));
	entry->key = malloc(sizeof(char) * (e + 1));
	entry->value = malloc(sizeof(char) * (ft_strlen(envp) - e + 1));
	if (!entry || !entry->key || !entry->value)
	{
		if (entry)
			free(entry);
		if (entry->key)
			free(entry->key);
		entry->key = NULL;
		return (entry);
	}
	ft_strlcpy(entry->key, envp, e + 1);
	envp += e + 1;
	ft_strlcpy(entry->value, envp, ft_strlen(envp) + 1);
	return (entry);
}
