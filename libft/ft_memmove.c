/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samoreno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 08:29:18 by samoreno          #+#    #+#             */
/*   Updated: 2021/11/04 08:29:19 by samoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char		*ptr_d;
	const char	*ptr_s;
	size_t		i;
	size_t		j;

	ptr_d = (char *)dst;
	ptr_s = (const char *)src;
	i = (len - 1);
	j = (len - 1);
	if (ptr_d < ptr_s)
	{
		i = 0;
		while (i < len && (ptr_d || ptr_s))
		{
			ptr_d[i] = ptr_s[i];
			i++;
		}
		return (dst);
	}
	while (len && (ptr_d || ptr_s))
	{
		ptr_d[i--] = ptr_s[j--];
		len--;
	}
	return (dst);
}
