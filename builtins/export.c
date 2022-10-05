/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josuna-t <josuna-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 10:55:10 by samoreno          #+#    #+#             */
/*   Updated: 2022/08/08 15:38:18 by josuna-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_addexport(char **command, t_list *env);
static void	ft_orderprint(t_list *env, t_comm *comm);

int	ft_export(char **command, t_comm *comm, t_list *env, int iter)
{
	int	stat;

	stat = first_check_export(iter, command);
	if (iter != 0 && command[1][0])
	{
		while (iter >= 1)
		{
			if (ft_vars(command[iter]) != 0 || command[iter][0] == '-')
				stat = export_error(command, iter);
			else
			{
				if (ft_replace(command[iter], env) == 0)
					ft_used(command, iter);
				if (ft_replace(command[iter], env) == 2)
					exitfree(comm, print_error(-1, "export"), env);
			}
			iter--;
		}
		if (ft_addexport(command, env) == 1)
			exitfree(comm, print_error(-1, "export"), env);
	}
	else if (iter == 0)
		ft_orderprint(env, comm);
	return (stat);
}

static void	ft_orderprint(t_list *env, t_comm *comm)
{
	t_list	*copy;

	copy = ft_lstmap(env, ft_placeholder, ft_delcopy);
	if (!copy)
	{
		ft_lstclear(&copy, ft_delcopy);
		exitfree(comm, 1, env);
	}
	ft_order(copy);
	ft_lstclear(&copy, ft_delcopy);
}

static int	ft_addexport(char **command, t_list *env)
{
	int		i;
	t_dict	*entry;
	t_list	*add;

	i = count_split(command) - 1;
	while (i >= 1)
	{
		if (command[i][0])
		{
			entry = dict(command[i]);
			if (!entry->key)
				return (1);
			add = ft_lstnew((void *)entry);
			if (!add)
				return (1);
			ft_lstadd_back(&env, add);
			ft_used(command, i);
		}
		i--;
	}
	return (0);
}

void	ft_used(char **comm, int seen)
{
	int	iter;
	int	eq_seen;
	int	eq_comp;

	iter = 1;
	eq_seen = is_equal(comm[seen]);
	while (iter <= seen)
	{
		eq_comp = is_equal(comm[iter]);
		if (eq_comp == eq_seen)
		{
			if (ft_is_exact(comm[seen], comm[iter], eq_seen, 0) == 0)
				comm[iter][0] = 0;
		}
		iter++;
	}
}

int	ft_replace(char *comm, t_list *env)
{
	int		e;
	t_dict	*el;

	if (comm[0])
	{
		while (env)
		{
			el = env->content;
			e = is_equal(comm);
			if (is_equal(el->key) > e)
				e = is_equal(el->key);
			if (ft_is_exact(el->key, comm, e, 0) == 0 && ft_declared(comm) == 0)
				return (replace_export(comm, e, el));
			env = env->next;
		}
	}
	return (1);
}
