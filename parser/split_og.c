/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_og.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samoreno <samoreno@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 14:23:23 by samoreno          #+#    #+#             */
/*   Updated: 2022/08/04 11:47:01 by samoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*ft_temporal(char const *s, char c, int start);
static int	ft_fill_words(char const *s, char c, char **array, size_t word_c);
static void	ft_quote_open(int qts[2], char qt);

char	**ft_split_og(char const *s, char c)
{
	char		**array;
	size_t		word_c;

	if (!s)
		return (NULL);
	word_c = ft_count_words(s, c);
	array = malloc(sizeof(char *) * (word_c + 1));
	if (!array)
		return (NULL);
	if (ft_fill_words(s, c, array, word_c) == 0)
		return (NULL);
	return (array);
}

static void	ft_quote_open(int qts[2], char qt)
{
	if (qt == '"')
	{
		if (qts[0] == 0)
			qts[0] = 1;
		else
			qts[0] = 0;
	}
	else
	{
		if (qts[1] == 0)
			qts[1] = 1;
		else
			qts[1] = 0;
	}
}

int	ft_count_words(char const *s, char c)
{
	int	iter;
	int	count;
	int	qts[2];

	iter = 0;
	count = 0;
	qts[0] = 0;
	qts[1] = 0;
	if (!ft_strchr(s, c) && ft_strlen(s))
		return (1);
	if (s[iter] != c && ft_strlen(s))
	{
		if (s[iter] == '"' || s[iter] == '\'')
			ft_quote_open(qts, s[iter]);
		count++;
		iter++;
	}
	while (s[iter])
	{
		if ((s[iter] != c && s[iter]) && s[iter - 1] == c
			&& (qts[0] == 0 && qts[1] == 0))
			count++;
		iter++;
	}
	return (count);
}

static int	ft_fill_words(char const *s, char c, char **array, size_t word_c)
{
	size_t		word;
	size_t		iter;
	char		*temp;

	word = 0;
	iter = 0;
	while (s[iter] == c)
		iter++;
	while (word < word_c && iter < ft_strlen(s))
	{
		temp = ft_temporal(s, c, iter);
		if (!temp)
			return (aux_fill_words(array, word_c, temp));
		iter += ft_strlen(temp);
		while (s[iter] == c)
			iter++;
		array[word] = malloc(sizeof(char) * (ft_strlen(temp) + 1));
		if (!array[word])
			return (aux_fill_words(array, word_c, temp));
		ft_strlcpy(array[word++], temp, (ft_strlen(temp) + 1));
		free(temp);
	}
	array[word] = 0;
	return (1);
}

static char	*ft_temporal(char const *s, char c, int start)
{
	int		iter[3];
	int		qts[2];
	char	*temporal;

	iter[0] = 0;
	iter[1] = 0;
	iter[2] = start - 1;
	qts[0] = 0;
	qts[1] = 0;
	while (s[++iter[2]])
	{
		if (s[iter[2]] == '"' || s[iter[2]] == '\'')
			ft_quote_open(qts, s[iter[2]]);
		if (s[iter[2]] == c && qts[0] == 0 && qts[1] == 0)
			break ;
		iter[1]++;
	}
	temporal = malloc(sizeof(char) * (iter[1] + 1));
	if (!temporal)
		return (NULL);
	while (start < iter[2])
		temporal[iter[0]++] = s[start++];
	temporal[iter[0]] = 0;
	return (temporal);
}
