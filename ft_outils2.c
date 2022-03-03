/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_outils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samoreno <samoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 09:07:22 by samoreno          #+#    #+#             */
/*   Updated: 2022/03/01 12:19:49 by samoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_vars(char **command)
{
	int		comm;
	size_t	iter;
	int		equals;

	comm = 1;
	while (command[comm])
	{
		iter = 0;
		if (command[iter][0] == '-')
			return (1);
		while (command[comm][iter] && command[comm][iter] != '=')
			iter++;
		equals = iter;
		while (command[comm][equals] == '=')
			equals++;
		if ((equals - iter) != 1 && (equals - iter) != 0)
			return (1);
		comm++;
	}
	return (0);
}

int	ft_isequal(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '=' && str[i])
		i++;
	return (i);
}
