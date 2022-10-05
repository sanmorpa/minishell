/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_aux.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samoreno <samoreno@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 15:07:16 by samoreno          #+#    #+#             */
/*   Updated: 2022/08/05 21:22:06 by samoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	fill_chars(char *read, char *unquoted, int i, char qt);
static void	fill_unquoted(char *read, char *unquoted, t_list *env, int l_flag);

char	*change_numbers(char *og)
{
	int		i[2];
	char	*new;

	i[0] = 0;
	i[1] = 0;
	new = malloc(sizeof(char) * (ft_strlen(og) + 1));
	if (!new)
	{
		free(og);
		return (NULL);
	}
	while (og[i[0]])
	{
		if (og[i[0]] == 1)
			new[i[1]++] = '\'';
		else if (og[i[0]] == 2)
			new[i[1]++] = '"';
		else if (og[i[0]] != 1 && og[i[0]] != 2 && og[i[0]] != 3)
			new[i[1]++] = og[i[0]];
		i[0]++;
	}
	new[i[1]] = 0;
	free(og);
	return (new);
}

char	*without_quotes(char *read, t_list *env, int l_flag)
{
	char	*unquoted;

	unquoted = malloc(sizeof(char) * (count_quoted(read, env, l_flag) + 1));
	if (!unquoted)
		return (NULL);
	unquoted[0] = 0;
	fill_unquoted(read, unquoted, env, l_flag);
	if (l_flag == 1)
	{
		unquoted = change_numbers(unquoted);
		if (!unquoted)
			return (NULL);
	}
	free(read);
	return (unquoted);
}

static void	fill_unquoted(char *read, char *unquoted, t_list *env, int l_flag)
{
	int	i[2];

	i[0] = 0;
	while (read[i[0]])
	{
		if (l_flag == 0)
			i[1] = ft_strlen(unquoted);
		else
			i[1] = -1;
		if (read[i[0]] == '\'')
		{
			if (l_flag == 1)
				i[0] = fill_chars(read, unquoted, i[0], '\'');
			else
				sq_no_flag(unquoted, read, i);
		}
		else if (read[i[0]] == '"')
			fill_dqs(i, unquoted, env, read);
		else
			fill_dollar_nqt(read, unquoted, env, i);
	}
}

int	find_fill(char *read, char *unquoted, size_t i, t_list *env)
{
	t_dict	*el;
	size_t	j;

	i++;
	j = i;
	while (read[j] && (ft_isalnum(read[j]) || read[j] == '_' || read[j] == '?'
			|| read[j] == 1 || read[j] == 2 || read[j] == 3))
		j++;
	while (env)
	{
		el = env->content;
		if (check_value(read, el->key, i, j - i) == 0)
		{
			fill_find_fill(unquoted, el->value);
			return (ft_strlen(unquoted));
		}
		env = env->next;
	}
	return (0);
}

static int	fill_chars(char *read, char *unquoted, int i, char qt)
{
	int	j;

	j = ft_strlen(unquoted);
	i++;
	while (read[i] && read[i] != qt)
	{
		unquoted[j] = read[i];
		i++;
		j++;
	}
	unquoted[j] = 0;
	return (i + 1);
}
