/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samoreno <samoreno@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 12:03:44 by samoreno          #+#    #+#             */
/*   Updated: 2022/08/08 10:52:17 by samoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_erase(char *command, t_list **env);
static int	delete_first_node(t_list **head, char *command);
static int	unset_error(char **command, int iter);

int	ft_unset(char **comman, t_list **env)
{
	int	iter;
	int	stat;

	stat = 0;
	iter = count_split(comman);
	if (iter > 1)
	{
		while (--iter >= 1)
		{
			if (ft_vars(comman[iter]) == 0 && ft_erase(comman[iter], env) == 0)
				ft_used(comman, iter);
			else
			{
				if (ft_vars(comman[iter]) != 0 || ft_strchr(comman[iter], '='))
					stat = unset_error(comman, iter);
			}
		}
	}
	return (stat);
}

static int	unset_error(char **command, int iter)
{
	if (command)
	{
		ft_putstr_fd("minishell: unset: ", 2);
		print_error(22, command[iter]);
	}
	else
		print_error(22, "minishell: unset");
	return (1);
}

static int	ft_erase(char *command, t_list **env)
{
	size_t	e;
	t_list	*temp;
	t_dict	*el;

	if (command[0])
	{
		if (env == NULL || *env == NULL || delete_first_node(env, command) == 0)
			return (0);
		while ((*env)->next)
		{
			el = (*env)->next->content;
			e = is_equal_unset(command);
			if (ft_strlen(el->key) > e)
				e = ft_strlen(el->key);
			if (ft_is_exact(el->key, command, e, 0) == 0)
			{
				temp = (*env)->next;
				(*env)->next = (temp)->next;
				ft_lstdelone(temp, delcontent);
				return (0);
			}
			env = &(*env)->next;
		}
	}
	return (1);
}

static int	delete_first_node(t_list **head, char *command)
{
	int		e;
	t_list	*temp;
	t_dict	*el;

	el = (*head)->content;
	e = is_equal(command);
	if (is_equal(el->key) > e)
		e = is_equal(el->key);
	if (ft_is_exact(el->key, command, e, 0) == 0)
	{
		temp = *head;
		*head = temp->next;
		ft_lstdelone(temp, delcontent);
		return (0);
	}
	return (1);
}
