/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaned_aux.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samoreno <samoreno@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 14:00:28 by josuna-t          #+#    #+#             */
/*   Updated: 2022/08/05 12:24:49 by samoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	**movearray(char **newcommand, char *command, int *indt)
{
	char	**temp;
	int		ind2;

	ind2 = 0;
	temp = ft_split_og(command, ' ');
	while (temp[ind2] != 0)
		newcommand[(*indt)++] = temp[ind2++];
	free(command);
	free(temp);
	return (newcommand);
}

char	**split_commands(char **command)
{
	int		ind;
	int		indt;
	int		count;
	char	**newcommand;
	char	**temp;

	count = 0;
	ind = 0;
	indt = 0;
	if (count_split(command) == 0)
		return (command);
	while (command[ind] != 0)
	{
		count += ft_count_words(command[ind], ' ');
		ind++;
	}
	temp = malloc (sizeof(char *) * (count + 1));
	ind = 0;
	while (command[ind] != 0)
		newcommand = movearray(temp, command[ind++], &indt);
	newcommand[indt] = 0;
	free(command);
	return (newcommand);
}

int	find_dollars_aux(int qt, int i, char *el)
{
	if (qt == 0 && el[i] == '$' && el[i + 1] && (ft_isalnum(el[i + 1])
			|| el[i + 1] == '_' || el[i + 1] == 1 || el[i + 1] == 2
			|| el[i + 1] == 3))
		return (1);
	return (0);
}

void	quote_redirect(int i[2], char *unquoted, char *read, char redirect)
{
	unquoted[i[1]++] = '"';
	while (read[i[0]] == redirect)
	{
		unquoted[i[1]] = redirect;
		i[0]++;
		i[1]++;
	}
	unquoted[i[1]++] = '"';
	unquoted[i[1]] = 0;
}

int	aux_fill_words(char **array, size_t word_c, char *temp)
{
	if (array)
		ft_free(array, word_c);
	if (temp)
		free(temp);
	return (0);
}
