/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samoreno <samoreno@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 11:17:39 by samoreno          #+#    #+#             */
/*   Updated: 2022/07/06 09:31:54 by samoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	add_question(t_list *env);

t_list	*envlist(char **envp)
{
	t_list	*env;
	t_dict	*entry;
	int		i;

	i = 0;
	entry = dict(envp[i++]);
	if (!entry->key)
		return (NULL);
	env = ft_lstnew((void *)entry);
	while (envp[i])
	{
		entry = dict(envp[i++]);
		if (!entry->key)
		{
			ft_lstclear(&env, delcontent);
			return (NULL);
		}
		ft_lstadd_back(&env, ft_lstnew((void *)entry));
	}
	if (add_question(env) == 1)
		return (NULL);
	return (env);
}

static int	add_question(t_list *env)
{
	t_dict	*entry;

	entry = dict("?=0");
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
	int		e;

	e = is_equal(envp);
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

void	delcontent(void *content)
{
	t_dict	*dict;

	dict = content;
	free(dict->key);
	free(dict->value);
	free(dict);
}
