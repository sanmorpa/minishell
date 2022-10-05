/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dqt_exception.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samoreno <samoreno@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 11:24:17 by samoreno          #+#    #+#             */
/*   Updated: 2022/08/08 12:57:24 by samoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_dqt_dollar(char *read, size_t i, t_list *env)
{
	t_dict		*el;
	size_t		j;

	i++;
	j = i;
	while (read[j] && (ft_isalnum(read[j]) || read[j] == '_' || read[j] == '?'
			|| read[j] == 1 || read[j] == 2))
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
		if (read[i] == '$' && read[i + 1] && (ft_isalnum(read[i + 1])
				|| read[i + 1] == '_' || read[i + 1] == '?'
				|| read[i + 1] == 1 || read[i + 1] == 2 || read[i + 1] == 3))
		{
			j = find_fill(read, unquoted, i, env);
			i++;
			while (read[i] && (ft_isalnum(read[i]) || read[i] == '_'
					|| read[i] == '?' || read[i] == 1 || read[i] == 2
					|| read[i] == 3))
				i++;
		}
		else
		{
			unquoted[j++] = read[i++];
			unquoted[j] = 0;
		}
	}
	return (i + 1);
}

int	count_dq(char *read, int i, int j, t_list *env)
{
	i++;
	while (read[i] && read[i] != '"')
	{
		if (read[i] == '$' && read[i + 1] && (ft_isalnum(read[i + 1])
				|| read[i + 1] == '_' || read[i + 1] == '?'
				|| read[i + 1] == 1 || read[i + 1] == 2 || read[i + 1] == 3))
		{
			j += count_dqt_dollar(read, i, env);
			i++;
			while (read[i] && (ft_isalnum(read[i]) || read[i] == '_'
					|| read[i] == '?' || read[i] == 1 || read[i] == 2
					|| read[i] == 3))
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
	if (read[i[0]] == '$' && read[i[0] + 1] && read[i[0] + 1] != ' '
		&& read[i[0] + 1] != '$')
	{
		i[1] += find_fill(read, unquoted, i[0], env);
		i[0]++;
		while (read[i[0]] && (ft_isalnum(read[i[0]]) || read[i[0]] == '_'
				|| read[i[0]] == '?' || read[i[0]] == 1 || read[i[0]] == 2))
			i[0]++;
	}
	else
	{
		i[1] = ft_strlen(unquoted);
		unquoted[i[1]++] = read[i[0]++];
		unquoted[i[1]] = 0;
	}
}
