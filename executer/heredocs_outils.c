/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs_outils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josuna-t <josuna-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 11:51:36 by samoreno          #+#    #+#             */
/*   Updated: 2022/07/29 14:14:02 by josuna-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	count_heredoc(char *r, size_t i, t_list *env)
{
	t_dict		*el;
	size_t		j;

	i++;
	j = i;
	while (r[j] && r[j] != '"' && r[j] != ' ' && r[j] != '\'' && r[j] != '$'
		&& r[j] != '=')
		j++;
	while (env)
	{
		el = env->content;
		if (check_value(r, el->key, i, j - i) == 0)
			return (ft_strlen(el->value));
		env = env->next;
	}
	return (0);
}

static int	fill_heredoc_dollar(char *read, char *new, int i, t_list *env)
{
	t_dict		*el;
	size_t		j;

	i++;
	j = i;
	while (read[j] && read[j] != '"' && read[j] != ' ' && read[j] != '\''
		&& read[j] != '$' && read[j] != '=')
		j++;
	while (env)
	{
		el = env->content;
		if (check_value(read, el->key, i, j - i) == 0)
		{
			ft_strlcat(new, el->value,
				(ft_strlen(new) + ft_strlen(el->value) + 1));
			return (ft_strlen(new));
		}
		env = env->next;
	}
	return (0);
}

static void	fill_heredoc(char *read, char *new, t_list *env)
{
	int		i[2];

	i[0] = 0;
	i[1] = 0;
	new[0] = 0;
	while (read[i[0]])
	{
		if (read[i[0]] == '$')
		{
			i[1] = fill_heredoc_dollar(read, new, i[0], env);
			i[0]++;
			while (read[i[0]] && read[i[0]] != '"' && read[i[0]] != ' '
				&& read[i[0]] != '\'' && read[i[0]] != '$' && read[i[0]] != '=')
				i[0]++;
		}
		else
		{
			new[i[1]++] = read[i[0]++];
			new[i[1]] = 0;
		}
	}
	new[i[1]] = 0;
}

char	*count_fill_heredoc(char *r, t_list *env)
{
	int		i[2];
	char	*new;

	i[0] = 0;
	i[1] = 0;
	while (r[i[0]])
	{
		if (r[i[0]] == '$')
		{
			i[1] += count_heredoc(r, i[0]++, env);
			while (r[i[0] + 1] && r[i[0] + 1] != '"' && r[i[0] + 1] != ' '
				&& r[i[0] + 1] != '\'' && r[i[0] + 1] != '$')
				i[0]++;
		}
		else
			i[1]++;
		i[0]++;
	}
	new = malloc(sizeof(char) * (i[1] + 1));
	if (!new)
		return (NULL);
	fill_heredoc(r, new, env);
	free(r);
	return (new);
}
