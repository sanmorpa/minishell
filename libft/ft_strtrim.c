/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samoreno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 10:04:55 by samoreno          #+#    #+#             */
/*   Updated: 2021/11/05 10:04:56 by samoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_left(char const *s1, char const *set);
static int	ft_right(char const *s1, char const *set);

char	*ft_strtrim(char const *s1, char const *set)
{
	int		left;
	int		right;
	int		i;
	char	*ptr;

	if (!s1 || !set)
		return (NULL);
	left = ft_left(s1, set);
	right = ft_right(s1, set);
	i = 0;
	if (right < left)
		right = left;
	ptr = malloc(sizeof(char) * (right - left + 1));
	if (!ptr)
		return (NULL);
	while (left < right)
	{
		ptr[i] = s1[left];
		i++;
		left++;
	}
	ptr[i] = 0;
	return (ptr);
}

static int	ft_left(char const *s1, char const *set)
{
	int	count;
	int	i;
	int	j;

	i = 0;
	j = 0;
	count = 0;
	while (s1[j])
	{
		while (set[i])
		{
			if (s1[j] == set[i])
			{
				count++;
				break ;
			}
			i++;
		}
		if (!set[i])
			break ;
		j++;
		i = 0;
	}
	return (count);
}

static int	ft_right(char const *s1, char const *set)
{
	int	count;
	int	i;
	int	j;

	i = 0;
	j = (ft_strlen(s1) - 1);
	count = 0;
	while (j)
	{
		while (set[i])
		{
			if (s1[j] == set[i])
			{
				count++;
				break ;
			}
			i++;
		}
		if (!set[i])
			break ;
		j--;
		i = 0;
	}
	return (ft_strlen(s1) - count);
}
