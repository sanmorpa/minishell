/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samoreno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 09:15:41 by samoreno          #+#    #+#             */
/*   Updated: 2021/11/05 09:15:42 by samoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*dest;
	size_t	len_s;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	len_s = ft_strlen(s);
	if (len <= len_s)
		dest = malloc(sizeof(char) * (len + 1));
	else
		dest = malloc(sizeof(char) * (len_s + 1));
	if (!dest)
		return (NULL);
	if (start < len_s)
	{
		while (i < len && s[start])
			dest[i++] = s[start++];
	}
	dest[i] = 0;
	return (dest);
}
