/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samoreno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 09:26:46 by samoreno          #+#    #+#             */
/*   Updated: 2021/11/05 09:26:47 by samoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*joined;
	int		i;
	int		j;
	int		k;
	int		l;

	if (!s1 || !s2)
		return (NULL);
	i = ft_strlen(s1);
	j = ft_strlen(s2);
	k = 0;
	l = 0;
	joined = malloc(sizeof(char) * (i + j + 1));
	if (!joined)
		return (NULL);
	while (k != i)
	{
		joined[k] = s1[k];
		k++;
	}
	while (k != (j + i))
		joined[k++] = s2[l++];
	joined[k] = 0;
	return (joined);
}
