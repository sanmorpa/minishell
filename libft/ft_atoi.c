/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samoreno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 11:15:26 by samoreno          #+#    #+#             */
/*   Updated: 2021/11/04 11:15:39 by samoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	negs;
	int	return_number;

	i = 0;
	negs = 0;
	return_number = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			negs++;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		return_number = (return_number * 10) + (str[i] - '0');
		i++;
	}
	if (negs)
		return_number *= -1;
	return (return_number);
}
