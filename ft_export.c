/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samoreno <samoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 10:55:10 by samoreno          #+#    #+#             */
/*   Updated: 2022/03/02 16:12:48 by samoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_addexport(char **command, t_list *env);
static int	ft_replace(char *command, t_list *env);
static void	ft_orderprint(t_list *env, char **command);

void	ft_export(char **command, t_list *env)
{
	int		iter;

	iter = ft_count_split(command) - 1;
	if (iter != 0)
	{
		if (ft_vars(command) == 0 && command[1][0] != '-')
		{
			while (iter >= 1)
			{
				if (ft_replace(command[iter], env) == 2)
					ft_exitfree(command, 1, env);
				if (ft_replace(command[iter], env) == 0)
					ft_used(command, iter);
				iter--;
			}
			if (ft_addexport(command, env) == 1)
				ft_exitfree(command, 1, env);
		}
		else
			printf("Input not valid\n");
	}
	else
		ft_orderprint(env, command);
}

static void	ft_orderprint(t_list *env, char **command)
{
	t_list	*copy;

	copy = ft_lstmap(env, ft_placeholder, ft_delcopy);
	if (!copy)
	{
		ft_lstclear(&copy, ft_delcopy);
		ft_exitfree(command, 1, env);
	}
	ft_order(copy);
	ft_lstclear(&copy, ft_delcopy);
}

static int	ft_addexport(char **command, t_list *env)
{
	int		i;
	t_dict	*entry;
	t_list	*add;

	i = 1;
	while (command[i])
	{
		if (command[i][0])
		{
			entry = ft_dict(command[i]);
			if (!entry->key)
				return (1);
			add = ft_lstnew((void *)entry);
			ft_lstadd_back(&env, add);
		}
		i++;
	}
	return (0);
}

void	ft_used(char **comm, int seen)
{
	int	iter;
	int	eq_seen;
	int	eq_comp;

	iter = 1;
	eq_seen = ft_isequal(comm[seen]);
	while (iter <= seen)
	{
		eq_comp = ft_isequal(comm[iter]);
		if (eq_comp == eq_seen)
		{
			if (ft_is_exact(comm[seen], comm[iter], eq_seen) == 0)
				comm[iter][0] = 0;
		}
		iter++;
	}
}

static int	ft_replace(char *command, t_list *env)
{
	int		e;
	t_dict	*el;

	if (command[0])
	{
		while (env)
		{
			el = env->content;
			e = ft_isequal(command);
			if (ft_isequal(el->key) > e)
				e = ft_isequal(el->key);
			if (ft_is_exact(el->key, command, e) == 0)
			{
				free(el->value);
				el->value = malloc(sizeof(char) * (ft_strlen(command) - e + 1));
				if (!el->value)
					return (2);
				command += e + 1;
				ft_strlcpy(el->value, command, ft_strlen(command) + 1);
				return (0);
			}
			env = env->next;
		}
	}
	return (1);
}
