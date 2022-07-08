/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samoreno <samoreno@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 09:35:52 by samoreno          #+#    #+#             */
/*   Updated: 2022/07/06 13:53:59 by samoreno         ###   ########.fr       */
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
		command.parsed = NULL;
		command.piped = NULL;
		command.og = line;
		command.parsed = without_quotes(line, env);
		if (!command.parsed)
			exitfree(NULL, &command, print_error(-1), env);
		command.piped = ft_split(command.parsed, '|');
		if (!command.piped)
			exitfree(NULL, &command, print_error(-1), env);
		ft_simple(&command, env);
		free(command.parsed);
		ft_free(command.piped, count_split(command.piped));
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
			fill_dollar_nqt(read, unquoted, env, i);
	}
}

int	find_fill(char *read, char *unquoted, size_t i, t_list *env)
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
		{
			ft_strlcat(unquoted, el->value,
				(ft_strlen(unquoted) + ft_strlen(el->value) + 1));
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
