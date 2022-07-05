/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outils1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samoreno <samoreno@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 17:29:38 by samoreno          #+#    #+#             */
/*   Updated: 2022/07/04 09:38:33 by samoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_exact(const char *src, const char *search, size_t n)
{
	size_t	iter;

	iter = 0;
	if ((n > ft_strlen(src) || n > ft_strlen(search))
		&& ft_strlen(src) != ft_strlen(search))
		return (1);
	while (src[iter] && search[iter] && iter < n)
	{
		if (src[iter] != search[iter])
			break ;
		iter++;
	}
	if (iter == ft_strlen(src) || iter == n)
		return (0);
	return (1);
}
