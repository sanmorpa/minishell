/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samoreno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 08:30:07 by samoreno          #+#    #+#             */
/*   Updated: 2021/11/04 08:30:08 by samoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	len_d;
	size_t	len_s;
	size_t	h;
	size_t	k;

	len_d = ft_strlen(dst);
	len_s = ft_strlen(src);
	k = 0;
	h = len_d;
	if (len_d < (size - 1) && size)
	{
		while (src[k] && k < (size - len_d - 1))
		{
			dst[h] = src[k];
			h++;
			k++;
		}
		dst[h] = 0;
	}
	if (len_d >= size)
		return (size + len_s);
	return (len_d + len_s);
}
