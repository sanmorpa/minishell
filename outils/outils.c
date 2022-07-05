/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samoreno <samoreno@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 11:35:34 by samoreno          #+#    #+#             */
/*   Updated: 2022/07/05 10:52:29 by samoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '=' && str[i])
		i++;
	return (i);
}

int	is_number(char *str)
{
	int	iter;

	iter = 0;
	while (str[iter])
	{
		if (ft_isdigit(str[iter]) == 0)
			return (1);
		iter++;
	}
	return (0);
}

int	count_split(char **split)
{
	int	iter;

	iter = 0;
	while (split[iter])
		iter++;
	return (iter);
}
