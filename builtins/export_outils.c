/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_outils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samoreno <samoreno@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 10:41:24 by samoreno          #+#    #+#             */
/*   Updated: 2022/08/04 11:16:27 by samoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_isprev(t_list *now, t_list *next);
static void	ft_printexport(t_dict *el);

int	ft_declared(char *comm)
{
	if ((size_t)is_equal(comm) != ft_strlen(comm))
		return (0);
	comm[0] = 0;
	return (1);
}

void	ft_order(t_list *env)
{
	t_list	*actual;
	t_list	*next;
	t_list	*head;

	head = env;
	while (env->next)
	{
		actual = env;
		next = env->next;
		while (next->next)
		{
			if (next->content && actual->content
				&& ft_isprev(actual, next) == 1)
				actual = next;
			next = next->next;
		}
		ft_printexport(actual->content);
		actual->content = NULL;
		while (!head->content)
			head = head->next;
		env = head;
	}
	ft_printexport(((t_dict *)env->content));
}

static int	ft_isprev(t_list *now, t_list *next)
{
	t_dict	*d_now;
	t_dict	*d_next;
	size_t	len;

	d_now = now->content;
	d_next = next->content;
	len = ft_strlen(d_now->key);
	if (len < ft_strlen(d_next->key))
		len = ft_strlen(d_next->key);
	if (ft_strncmp(d_now->key, d_next->key, len) > 0)
		return (1);
	return (0);
}

static void	ft_printexport(t_dict *el)
{
	if (ft_is_exact(el->key, "?", ft_strlen(el->key), 0) != 0
		&& ft_is_exact(el->key, "_", ft_strlen(el->key), 0) == 1)
	{
		printf("declare -x %s", el->key);
		if (el->value)
			print_export_values(el);
		printf("\n");
	}
}

void	fill_value_dict(size_t e, t_dict *entry, char *envp)
{
	if (entry->key && (e != ft_strlen(envp) || envp[e - 1] == '='))
	{
		envp += e + 1;
		copy_export(entry->value, envp);
	}
}
