/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_comm.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josuna-t <josuna-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 11:20:18 by samoreno          #+#    #+#             */
/*   Updated: 2022/08/08 16:56:54 by josuna-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	refill_command_comm(char *og, char *comm, int i[2]);
static void	count_command_comm(char *og, int i[2]);

char	**fill_command_comm(char *original, t_list *env, t_element *el)
{
	int		i[2];
	char	*command;
	char	**split_comm;

	i[0] = 0;
	i[1] = 0;
	if (is_there_redirections(original) == 0)
	{
		command = malloc(sizeof(char) * (ft_strlen(original) + 1));
		if (!command)
			return (NULL);
		ft_strlcpy(command, original, ft_strlen(original) + 1);
		split_comm = dollars_command(command, env, -1, el);
		return (split_comm);
	}
	count_command_comm(original, i);
	command = malloc(sizeof(char) * (i[1] + 1));
	if (!command)
		return (NULL);
	i[0] = 0;
	i[1] = 0;
	refill_command_comm(original, command, i);
	split_comm = dollars_command(command, env, -1, el);
	return (split_comm);
}

static void	refill_comm_red(char *og, int i[2], int quote)
{
	while (og[i[0]] && (og[i[0]] == '<' || og[i[0]] == '>'))
	i[0]++;
	while (og[i[0]] && og[i[0]] == ' ')
		i[0]++;
	while (og[i[0]] && (og[i[0]] != ' ' || quote != 0))
	{
		if (og[i[0]] == '"' || og[i[0]] == '\'')
		{
			quote = open_quotes(og[i[0]], quote);
			i[0]++;
		}
		else
			i[0]++;
	}
}

static void	refill_command_comm(char *og, char *comm, int i[2])
{
	int	quote;

	quote = 0;
	while (og[i[0]])
	{
		if (og[i[0]] == '"' || og[i[0]] == '\'')
		{
			quote = open_quotes(og[i[0]], quote);
			comm[i[1]++] = og[i[0]++];
		}
		else
		{
			if (quote != 0)
				comm[i[1]++] = og[i[0]++];
			else
			{
				if (og[i[0]] == '<' || og[i[0]] == '>')
					refill_comm_red(og, i, quote);
				else
					comm[i[1]++] = og[i[0]++];
			}
		}
	}
	comm[i[1]] = 0;
}

static void	count_comm_red(char *og, int i[2], int quote)
{
	if (og[i[0]] == '<' || og[i[0]] == '>')
	{
		while (og[i[0]] && (og[i[0]] == '<' || og[i[0]] == '>'))
			i[0]++;
		while (og[i[0]] && og[i[0]] == ' ')
			i[0]++;
		while (og[i[0]] && (og[i[0]] != ' ' || quote != 0))
		{
			if (og[i[0]] == '"' || og[i[0]] == '\'')
			{
				quote = open_quotes(og[i[0]], quote);
				i[0]++;
			}
			else
				i[0]++;
		}
	}
	else
	{
		i[0]++;
		i[1]++;
	}
}

static void	count_command_comm(char *og, int i[2])
{
	int	quote;

	quote = 0;
	while (og[i[0]])
	{
		if (og[i[0]] == '"' || og[i[0]] == '\'')
		{
			quote = open_quotes(og[i[0]], quote);
			i[0]++;
			i[1]++;
		}
		else
		{
			if (quote != 0)
			{
				i[0]++;
				i[1]++;
			}
			else
				count_comm_red(og, i, quote);
		}
	}
}
