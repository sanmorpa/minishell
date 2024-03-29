/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samoreno <samoreno@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 11:59:06 by samoreno          #+#    #+#             */
/*   Updated: 2022/07/29 14:24:29 by samoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_words(char const *s, char c);
static char	*ft_temporal(char const *s, char c, int start);
static int	ft_fill_words(char const *s, char c, char **array, size_t word_c);

static int	ft_free(char **array, int words, char *temp, int i)
{
	int	iter;

	iter = 0;
	while (iter < words)
	{
		if (array[iter])
			free(array[iter]);
		iter++;
	}
	if (array)
		free(array);
	if (temp)
		free(temp);
	return (i);
}

char	**ft_split(char const *s, char c)
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

static int	ft_count_words(char const *s, char c)
{
	int	iter;
	int	count;

	iter = 0;
	count = 0;
	if (!ft_strchr(s, c) && ft_strlen(s))
		return (1);
	if (s[iter] != c && ft_strlen(s))
	{
		count++;
		iter++;
	}
	while (s[iter])
	{
		if ((s[iter] != c && s[iter]) && s[iter - 1] == c)
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
			return (ft_free(array, word_c, NULL, 0));
		iter += ft_strlen(temp);
		while (s[iter] == c)
			iter++;
		array[word] = malloc(sizeof(char) * (ft_strlen(temp) + 1));
		if (!array[word])
			return (ft_free(array, word_c, temp, 0));
		ft_strlcpy(array[word++], temp, (ft_strlen(temp) + 1));
		free(temp);
	}
	array[word] = 0;
	return (1);
}

static char	*ft_temporal(char const *s, char c, int start)
{
	int		iter;
	int		chr;
	int		start_tem;
	char	*temporal;

	iter = 0;
	chr = 0;
	start_tem = start;
	while (s[start_tem])
	{
		if (s[start_tem] == c)
			break ;
		chr++;
		start_tem++;
	}
	temporal = malloc(sizeof(char) * (chr + 1));
	if (!temporal)
		return (NULL);
	while (start < start_tem)
		temporal[iter++] = s[start++];
	temporal[iter] = 0;
	return (temporal);
}
