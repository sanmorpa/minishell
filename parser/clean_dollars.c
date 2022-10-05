/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_dollars.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samoreno <samoreno@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 15:52:53 by samoreno          #+#    #+#             */
/*   Updated: 2022/08/09 10:10:48 by samoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	find_dollars_dollars(char **elp, char *el,
	t_list *env, t_element *elm)
{
	int	qt;
	int	i;

	i = -1;
	qt = 0;
	if (ft_strlen(el) >= 3 && el[1] == '<' && el[2] == '<')
	{
		*elp = filehere(el, ft_strlen(el), env, elm);
		return (0);
	}
	while (el[++i])
	{
		if (el[i] == '\'' || el[i] == 3)
		{
			if (qt == 0)
				qt = 1;
			else
				qt = 0;
		}
		if (qt == 0 && el[i] == '$' && el[i + 1] && (ft_isalnum(el[i + 1])
				|| el[i + 1] == '_' || el[i + 1] == 1 || el[i + 1] == 2
				|| el[i + 1] == 3))
			return (1);
	}
	return (0);
}

static char	*clean_quotes(char *com, t_list *env, t_element *elm)
{
	while (find_dollars_dollars(&com, com, env, elm) == 1)
	{
		com = without_quotes(com, env, 0);
		if (!com)
			return (NULL);
	}
	clean_tabs(com);
	return (com);
}

char	**dollars_command(char *com, t_list *env, int i, t_element *elm)
{
	char	**split;

	com = clean_quotes(com, env, elm);
	if (!com)
		return (NULL);
	split = ft_split_og(com, ' ');
	if (!split)
		return (NULL);
	split = split_commands(split);
	if (!split)
		return (NULL);
	while (++i < count_split(split))
	{
		if (split[i][0] != '<' || split[i][1] != '<')
		{
			split[i] = without_quotes(split[i], env, 1);
			if (!split[i])
			{
				ft_free(split, count_split(split));
				return (NULL);
			}
		}
	}
	free(com);
	return (split);
}

int	check_pipes(char *read)
{
	int	i;
	int	pipe;

	i = 0;
	pipe = 0;
	if (read[0] == '|' || read[ft_strlen(read) - 1] == '|')
		return (1);
	while (read[i])
	{
		if (read[i] == '|')
		{
			if (pipe == 0)
				pipe = 1;
			else
				return (1);
		}
		else if (read[i] != ' ')
			pipe = 0;
		i++;
	}
	return (0);
}

void	fill_find_fill(char *unquoted, char *read)
{
	int	i;
	int	j;

	i = ft_strlen(unquoted);
	j = 0;
	while (read[j])
	{
		if (read[j] == 3)
			unquoted[i] = '\'';
		else
			unquoted[i] = read[j];
		j++;
		i++;
	}
		unquoted[i] = 0;
}
