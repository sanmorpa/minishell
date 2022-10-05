/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josuna-t <josuna-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 13:27:18 by samoreno          #+#    #+#             */
/*   Updated: 2022/08/08 17:26:28 by josuna-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ignore_qt(int i, char *read, char quote);
static int	count_chars(char *read, int i[2], int j, char qt);
static void	count_simple(char *read, int i[2], t_list *env);

int	closed_quotes(char *read)
{
	int	i;

	i = 0;
	if (check_pipes(read) || check_reds(read) == 1)
		return (1);
	while (read[i])
	{
		if (read[i + 1] && read[i] == '>' && read[i + 1] == '<')
			return (1);
		if (read[i] && (read[i] == '\'' || read[i] == '"'))
			i = ignore_qt(i, read, read[i]);
		if (i == -1)
			return (1);
		if (i == -1)
			return (1);
		i++;
	}
	if (read[i - 1] == '>' || read[i - 1] == '<')
		return (1);
	return (0);
}

static int	ignore_qt(int i, char *read, char quote)
{
	i++;
	while (read[i])
	{
		if (read[i] && read[i] == quote)
			return (i);
		i++;
	}
	return (-1);
}

int	count_quoted(char *read, t_list *env, int l_flag)
{
	int	i[2];

	i[0] = 0;
	i[1] = 0;
	while (read[i[0]])
	{
		if (read[i[0]] == '\'')
		{
			if (l_flag == 1)
				i[1] = count_chars(read, i, i[1], '\'');
			else
				simple_quote_no_last(read, i);
		}
		else if (read[i[0]] == '"')
		{
			i[1] += count_dq(read, i[0], i[1], env) + 2;
			count_chars(read, i, i[1], '"');
		}
		else
			count_simple(read, i, env);
	}
	return (i[1]);
}

static void	count_simple(char *read, int i[2], t_list *env)
{
	if (read[i[0]] == '$' && read[i[0] + 1] && read[i[0] + 1] != ' '
		&& read[i[0] + 1] != '$')
	{
		i[1] += count_dqt_dollar(read, i[0], env);
		i[0]++;
		while (read[i[0]] && (ft_isalnum(read[i[0]]) || read[i[0]] == '_'
				|| read[i[0]] == '?' || read[i[0]] == 1 || read[i[0]] == 2))
			i[0]++;
	}
	else if (read[i[0]] == '<' || read[i[0]] == '>')
	{
		i[1] += 3;
		if (read[i[0] + 1] == '<' || read[i[0] + 1] == '>')
		{
			i[0]++;
			i[1]++;
		}
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
