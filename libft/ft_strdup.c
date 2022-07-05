/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samoreno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 09:15:25 by samoreno          #+#    #+#             */
/*   Updated: 2021/11/05 09:15:27 by samoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	int		i;
	char	*ptr;

	i = 0;
	while (s1[i])
		i++;
	ptr = malloc(sizeof(const char) * (i + 1));
	if (!ptr)
		return (NULL);
	ptr = (char *)ft_memcpy(ptr, s1, i);
	ptr[i] = 0;
	return (ptr);
}
