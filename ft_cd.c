/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samoreno <samoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 12:35:56 by samoreno          #+#    #+#             */
/*   Updated: 2022/03/04 09:49:08 by samoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_oldpwd(t_list *env, char *newpwd);

void	ft_cd(char **command, t_list *env)
{
	int	n;

	n = ft_count_split(command);
	if (n != 2)
		printf("Error: invalid syntax\n");
	else
	{
		if (ft_oldpwd(env, command[1]) == 2)
			ft_exitfree(command, 1, env);
	}
}

static int	ft_newpwd(t_list *env, char *newpwd)
{
	t_dict	*el;
	size_t	n;

	while (env)
	{
		el = env->content;
		n = ft_strlen(el->key);
		if (ft_strlen("PWD") > n)
			n = ft_strlen("PWD");
		if (ft_is_exact("PWD", el->key, n) == 0)
		{
			free(el->value);
				el->value = malloc(sizeof(char) * (ft_strlen(newpwd) + 1));
			if (!el->value)
				return (2);
			ft_strlcpy(el->value, newpwd, ft_strlen(newpwd) + 1);
			return (0);
		}
		env = env->next;
	}
	return (1);
}

static int	ft_newpwd(t_list *env, char *newpwd)
{
	t_dict	*el;
	size_t	n;

	while (env)
	{
		el = env->content;
		n = ft_strlen(el->key);
		if (ft_strlen("PWD") > n)
			n = ft_strlen("PWD");
		if (ft_is_exact("PWD", el->key, n) == 0)
		{
			free(el->value);
				el->value = malloc(sizeof(char) * (ft_strlen(newpwd) + 1));
			if (!el->value)
				return (2);
			ft_strlcpy(el->value, newpwd, ft_strlen(newpwd) + 1);
			return (0);
		}
		env = env->next;
	}
	return (1);
}
