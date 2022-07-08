/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dqt_exception.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samoreno <samoreno@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 11:24:17 by samoreno          #+#    #+#             */
/*   Updated: 2022/07/06 13:53:00 by samoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_dqt_dollar(char *read, size_t i, t_list *env)
{
	t_dict		*el;
	size_t		j;

	i++;
	j = i;
	while (read[j] && read[j] != '"' && read[j] != ' ' && read[j] != '\'')
		j++;
	while (env)
	{
		el = env->content;
		if (check_value(read, el->key, i, j - i) == 0)
			return (ft_strlen(el->value));
		env = env->next;
	}
	return (0);
}

int	check_value(char *var, char *env, size_t n, size_t k)
{
	size_t	iter;

	iter = 0;
	if (ft_strlen(env) != k)
		return (1);
	while (var[n] && env[iter] && iter < k)
	{
		if (var[n] != env[iter])
			break ;
		iter++;
		n++;
	}
	if (iter == ft_strlen(var) || iter == k)
		return (0);
	return (1);
}

int	fill_dq_dollar(char *read, char *unquoted, int i, t_list *env)
{
	int	j;

	j = ft_strlen(unquoted);
	i++;
	while (read[i] && read[i] != '"')
	{
		if (read[i] == '$')
		{
			j = find_fill(read, unquoted, i, env);
			while (read[i] && read[i] != ' ' && read[i] != '"'
				&& read[i] != '\'')
				i++;
		}
		else
		{
			unquoted[j] = read[i];
			j++;
			unquoted[j] = 0;
			i++;
		}
	}
	return (i + 1);
}

int	count_dq(char *read, int i, int j, t_list *env)
{
	i++;
	while (read[i] && read[i] != '"')
	{
		if (read[i] == '$')
		{
			j += count_dqt_dollar(read, i, env);
			while (read[i] && read[i] != ' ' && read[i] != '"')
				i++;
		}
		else
		{
			j++;
			i++;
		}
	}
	return (j);
}

void	fill_dollar_nqt(char *read, char *unquoted, t_list *env, int i[2])
{
	if (read[i[0]] == '$')
	{
		i[1] += find_fill(read, unquoted, i[0], env);
		while (read[i[0]] && read[i[0]] != ' ' && read[i[0]] != '"'
			&& read[i[0]] != '\'')
			i[0]++;
	}
	else
	{
		i[1] = ft_strlen(unquoted);
		unquoted[i[1]++] = read[i[0]++];
		unquoted[i[1]] = 0;
	}
}
