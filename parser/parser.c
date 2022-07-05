/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samoreno <samoreno@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 09:35:52 by samoreno          #+#    #+#             */
/*   Updated: 2022/07/05 15:11:43 by samoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*without_quotes(char *read, t_list *env);
static int	fill_chars(char *read, char *unquoted, int i, char qt);
static void	fill_unquoted(char *read, char *unquoted, t_list *env);

void	parser(char *line, t_list *env)
{
	t_comm	command;

	if (closed_quotes(line) == 1)
		print_error(22);
	else
	{
		command.og = line;
		command.parsed = without_quotes(line, env);
		command.piped = ft_split(command.parsed, '|');
		ft_simple(&command, env);
		free(command.parsed);
	}
}

static char	*without_quotes(char *read, t_list *env)
{
	int		i;
	char	*unquoted;

	i = 0;
	unquoted = malloc(sizeof(char) * (count_quoted(read, env) + 1));
	if (!unquoted)
		exit(print_error(-1));
	unquoted[0] = 0;
	fill_unquoted(read, unquoted, env);
	return (unquoted);
}

static void	fill_unquoted(char *read, char *unquoted, t_list *env)
{
	int	i[2];

	i[0] = 0;
	while (read[i[0]])
	{
		if (read[i[0]] == '\'')
			i[0] = fill_chars(read, unquoted, i[0], '\'');
		else if (read[i[0]] == '"')
			i[0] = fill_dq_dollar(read, unquoted, i[0], env);
		else
		{
			if (read[i[0]] == '$')
			{
				i[1] += find_fill(read, unquoted, i[0], env);
				while (read[i[0]] && read[i[0]] != ' ' && read[i[0]] != '"')
					i[0]++;
			}
			else
			{
				i[1] = ft_strlen(unquoted);
				unquoted[i[1]++] = read[i[0]++];
				unquoted[i[1]] = 0;
			}
		}
	}
}

int	find_fill(char *read, char *unquoted, size_t i, t_list *env)
{
	t_dict		*el;
	size_t		j;

	i++;
	j = i;
	while (read[j] && read[j] != '"' && read[j] != ' ')
		j++;
	while (env)
	{
		el = env->content;
		if (check_value(read, el->key, i, j - i) == 0)
		{
			ft_strlcat(unquoted, el->value,
				(ft_strlen(unquoted) + ft_strlen(el->value) + 1));
			return (j);
		}
		env = env->next;
	}
	return (j);
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