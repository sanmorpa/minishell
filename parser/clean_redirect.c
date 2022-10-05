/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_redirect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josuna-t <josuna-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 11:14:38 by samoreno          #+#    #+#             */
/*   Updated: 2022/08/08 17:32:04 by josuna-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	refill_command_red(char *og, char *comm, int i[2]);
static void	count_command_red(char *og, int i[2]);

char	**fill_command_red(char *original, t_list *env, t_element *elm)
{
	int		i[2];
	char	*command;
	char	**split_comm;

	i[0] = 0;
	i[1] = 0;
	if (is_there_redirections(original) == 0)
	{
		split_comm = ft_split(" ", ' ');
		return (split_comm);
	}
	count_command_red(original, i);
	command = malloc(sizeof(char) * (i[1] + 1));
	if (!command)
		return (NULL);
	i[0] = 0;
	i[1] = 0;
	refill_command_red(original, command, i);
	split_comm = dollars_command(command, env, -1, elm);
	return (split_comm);
}

static void	refill_red_red(char *og, char *comm, int i[2], int quote)
{
	comm[i[1]++] = ' ';
	while (og[i[0]] && (og[i[0]] == '<' || og[i[0]] == '>'))
	comm[i[1]++] = og[i[0]++];
	while (og[i[0]] && og[i[0]] == ' ')
	i[0]++;
	while (og[i[0]] && (og[i[0]] != ' ' || quote != 0))
	{
		if (og[i[0]] == '"' || og[i[0]] == '\'')
		{
			quote = open_quotes(og[i[0]], quote);
			comm[i[1]++] = og[i[0]++];
		}
		else
			comm[i[1]++] = og[i[0]++];
	}
}

static void	refill_command_red(char *og, char *comm, int i[2])
{
	int	quote;

	quote = 0;
	while (og[i[0]])
	{
		if (og[i[0]] == '"' || og[i[0]] == '\'')
		{
			quote = open_quotes(og[i[0]], quote);
			i[0]++;
		}
		else
		{
			if (quote != 0)
				i[0]++;
			else
			{
				if (og[i[0]] == '<' || og[i[0]] == '>')
					refill_red_red(og, comm, i, quote);
				else
					i[0]++;
			}
		}
	}
	comm[i[1]] = 0;
}

static void	count_red_red(char *og, int i[2], int quote)
{
	i[1]++;
	while (og[i[0]] && (og[i[0]] == '<' || og[i[0]] == '>'))
	{
		i[0]++;
		i[1]++;
	}
	while (og[i[0]] && og[i[0]] == ' ')
		i[0]++;
	while (og[i[0]] && (og[i[0]] != ' ' || quote != 0))
	{
		if (og[i[0]] == '"' || og[i[0]] == '\'')
		{
			quote = open_quotes(og[i[0]], quote);
			{
				i[0]++;
				i[1]++;
			}
		}
		else
		{
			i[0]++;
			i[1]++;
		}
	}
}

static void	count_command_red(char *og, int i[2])
{
	int	quote;

	quote = 0;
	while (og[i[0]])
	{
		if (og[i[0]] == '"' || og[i[0]] == '\'')
		{
			quote = open_quotes(og[i[0]], quote);
			i[0]++;
		}
		else
		{
			if (quote != 0)
				i[0]++;
			else
			{
				if (og[i[0]] == '<' || og[i[0]] == '>')
					count_red_red(og, i, quote);
				else
					i[0]++;
			}
		}
	}
}
