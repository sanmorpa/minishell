/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samoreno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 10:18:27 by samoreno          #+#    #+#             */
/*   Updated: 2021/11/04 10:19:00 by samoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const char	*ptr_s;
	size_t		i;

	ptr_s = s;
	i = 0;
	if (c > 127)
		c = (unsigned char)c;
	while (i < n)
	{
		if (ptr_s[i] == c)
			return ((void *)&ptr_s[i]);
		i++;
	}
	return (NULL);
}
