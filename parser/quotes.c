/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samoreno <samoreno@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 13:27:18 by samoreno          #+#    #+#             */
/*   Updated: 2022/07/06 10:29:55 by samoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ignore_qt(int i, char *read, char quote);
static int	count_chars(char *read, int i[2], int j, char qt);
static void	count_simple(char *read, int i[2], t_list *env);

int	closed_quotes(char *read)
{
	int	i;
	int	j;
	int	quote;

	i = 0;
	j = ft_strlen(read) - 1;
	quote = -1;
	while (read[i])
	{
		if (read[i] == '\'')
			i = ignore_qt(i, read, '\'');
		else if (read[i] == '"')
			i = ignore_qt(i, read, '"');
		if (i == -1)
			return (1);
		i++;
	}
	return (0);
}

static int	ignore_qt(int i, char *read, char quote)
{
	i++;
	while (read[i])
	{
		if (read[i] == quote)
			return (i);
		i++;
	}
	return (-1);
}

int	count_quoted(char *read, t_list *env)
{
	int	i[2];

	i[0] = 0;
	i[1] = 0;
	while (read[i[0]])
	{
		if (read[i[0]] == '\'')
		{
			i[1] = count_chars(read, i, i[1], '\'');
		}
		else if (read[i[0]] == '"')
		{
			i[1] += count_dq(read, i[0], i[1], env);
			count_chars(read, i, i[1], '"');
		}
		else
			count_simple(read, i, env);
	}
	return (i[1]);
}

static void	count_simple(char *read, int i[2], t_list *env)
{
	if (read[i[0]] == '$')
	{
		i[1] += count_dqt_dollar(read, i[0], env);
		while (read[i[0]] && read[i[0]] != ' ' && read[i[0]] != '"'
			&& read[i[0]] != '\'')
			i[0]++;
	}
	else
	{
		i[1]++;
		i[0]++;
	}
}

static int	count_chars(char *read, int i[2], int j, char qt)
{
	i[0]++;
	while (read[i[0]] && read[i[0]] != qt)
	{
		j++;
		i[0]++;
	}
	i[0]++;
	return (j);
}
