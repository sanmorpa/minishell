/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samoreno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 10:22:50 by samoreno          #+#    #+#             */
/*   Updated: 2021/11/11 10:22:53 by samoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	len;
	size_t	i;
	char	*f_str;

	if (!s || !f)
		return (NULL);
	len = ft_strlen(s);
	i = 0;
	f_str = malloc(sizeof(char) * (len + 1));
	if (!f_str)
		return (NULL);
	while (s[i])
	{
		f_str[i] = s[i];
		i++;
	}
	f_str[len] = 0;
	i = 0;
	while (f_str[i])
	{
		f_str[i] = f(i, f_str[i]);
		i++;
	}
	return (f_str);
}
