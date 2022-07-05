/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samoreno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 10:59:47 by samoreno          #+#    #+#             */
/*   Updated: 2021/11/04 11:00:32 by samoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	int		j;
	int		size_str;

	size_str = ft_strlen(needle);
	i = 0;
	j = 0;
	if (!size_str)
		return ((char *)haystack);
	while (haystack[i] && needle[j] && i < len)
	{
		if (j == size_str)
			break ;
		if (haystack[i] == needle[j])
			j++;
		else
		{
			i -= j;
			j = 0;
		}
		i++;
	}
	if (j == size_str)
		return ((char *)(haystack + (i - j)));
	return (NULL);
}

/* int	main(void)
{
	char str[] = "aaabcabcd";n
	char str2[] = "aabc";

	printf("%s", ft_strnstr(str, "abcd", 9));
	return (0);
} */
