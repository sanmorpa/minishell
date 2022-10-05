/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_outils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samoreno <samoreno@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 10:43:24 by samoreno          #+#    #+#             */
/*   Updated: 2022/08/09 10:08:19 by samoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_there_redirections(char *original)
{
	int	i[2];

	i[0] = -1;
	i[1] = 0;
	while (original[++i[0]])
	{
		if (original[i[0]] == '"' || original[i[0]] == '\'')
		{
			if (i[1] == 0)
				i[1] = original[i[0]];
			else if (i[1] == original[i[0]])
				i[1] = 0;
		}
		if (i[1] == 0 && (original[i[0]] == '<' || original[i[0]] == '>'))
			return (1);
	}
	return (0);
}

int	open_quotes(char now, int quotes)
{
	if (now == '\'')
	{
		if (quotes == 0)
			return (1);
		if (quotes == 1)
			return (0);
	}
	if (quotes == 0)
		return (2);
	return (0);
}

void	fill_dqs(int i[2], char *unquoted, t_list *env, char *read)
{
	if (i[1] >= 0)
	{
		i[1] = ft_strlen(unquoted);
		unquoted[i[1]++] = '"';
		unquoted[i[1]] = 0;
	}
	i[0] = fill_dq_dollar(read, unquoted, i[0], env);
	if (i[1] >= 0)
	{
		i[1] = ft_strlen(unquoted);
		unquoted[i[1]++] = '"';
		unquoted[i[1]] = 0;
	}
}

void	sq_no_flag(char *unquoted, char *read, int i[2])
{
	i[1] = ft_strlen(unquoted);
	unquoted[i[1]++] = read[i[0]++];
	while (read[i[0]] && read[i[0]] != '\'')
		unquoted[i[1]++] = read[i[0]++];
	unquoted[i[1]++] = read[i[0]++];
	unquoted[i[1]] = 0;
}

void	clean_tabs(char *command)
{
	int		i;
	int		quote;

	i = 0;
	quote = 0;
	while (command[i])
	{
		if (command[i] == '\'' || command[i] == '"')
		{
			if (quote == 0)
				quote = command[i];
			else if (quote == command[i])
				quote = 0;
		}
		if (command[i] == '\t' && quote == 0)
			command[i] = ' ';
		i++;
	}
}
