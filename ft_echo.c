/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samoreno <samoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 11:15:50 by samoreno          #+#    #+#             */
/*   Updated: 2022/03/03 11:55:01 by samoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_printecho(char *str, t_list *env);
static void	ft_expand(char *str, int i, t_list *env);

void	ft_echo(char **command, t_list *env)
{
	size_t	n;
	int		iter;

	iter = 1;
	n = 0;
	if (ft_count_split(command) > 1)
	{
		while (command[iter] && ft_is_exact(command[iter], "-n",
				ft_strlen(command[iter])) == 0)
		{
			iter++;
			n++;
		}
		while (command[iter])
		{
			ft_printecho(command[iter], env);
			iter++;
		}
	}
	if (n == 0)
		printf("\n");
}

static void	ft_printecho(char *str, t_list *env)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != '$')
		{
			printf("%c", str[i]);
			i++;
		}
		else
		{
			ft_expand(str, i, env);
			while (str[i] && str[i] != ' ')
				i++;
		}
	}
}

static void	ft_expand(char *str, int i, t_list *env)
{
	t_dict	*el;
	size_t	n;
	int		ret;

	str += i + 1;
	while (env)
	{
		el = env->content;
		n = ft_strlen(el->key);
		if (ft_strlen(str) > n)
			n = ft_strlen(str);
		if (ft_is_exact(str, el->key, n) == 0)
		{
			ret = printf("%s", el->value);
			break ;
		}
		env = env->next;
	}
}
