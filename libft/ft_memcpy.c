/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samoreno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 08:29:10 by samoreno          #+#    #+#             */
/*   Updated: 2021/11/04 08:29:11 by samoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char		*ptr_d;
	const char	*ptr_s;
	size_t		i;

	ptr_d = (char *)dst;
	ptr_s = (const char *)src;
	i = 0;
	while (i < n && (ptr_d || ptr_s))
	{
		ptr_d[i] = ptr_s[i];
		i++;
	}
	return (dst);
}
