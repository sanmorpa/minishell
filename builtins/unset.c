/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samoreno <samoreno@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 12:03:44 by samoreno          #+#    #+#             */
/*   Updated: 2022/07/06 12:40:21 by samoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Debuggear por que no fucniona primero

static int	ft_erase(char *command, t_list **env);

void	ft_unset(char **command, t_comm *comm, t_list *env)
{
	int	iter;

	iter = count_split(command) - 1;
	if (iter > 0)
	{
		if (ft_vars(command) == 0)
		{
			while (iter >= 1)
			{
				if (ft_erase(command[iter], &env) == 2)
					exitfree(command, comm, 1, env);
				if (ft_erase(command[iter], &env) == 0)
					ft_used(command, iter);
				iter--;
			}
		}
	}
}

static int	ft_erase(char *command, t_list **env)
{
	int		e;
	t_list	*temp;
	t_dict	*el;

	if (command[0])
	{
		el = (*env)->content;
		e = ft_isequal(command);
		if (ft_isequal(el->key) > e)
			e = ft_isequal(el->key);
		if (ft_is_exact(el->key, command, e) == 0)
		{
			printf("entro\n");
			temp = (*env)->next;
			ft_lstdelone((*env), ft_delcontent);
			*env = temp;
			return (0);
		}
		while ((*env)->next)
		{
			el = (*env)->next->content;
			e = ft_isequal(command);
			if (ft_isequal(el->key) > e)
				e = ft_isequal(el->key);
			if (ft_is_exact(el->key, command, e) == 0)
			{
				temp = (*env)->next->next;
				ft_lstdelone((*env)->next, ft_delcontent);
				(*env)->next = temp;
				return (0);
			}
			env = &(*env)->next;
		}
	}
	return (1);
}
