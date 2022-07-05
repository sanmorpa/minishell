/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samoreno <samoreno@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 11:15:50 by samoreno          #+#    #+#             */
/*   Updated: 2022/07/05 15:12:50 by samoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(char **command, t_list *env)
{
	size_t	n;
	int		iter;

	iter = 1;
	n = 0;
	(void)env;
	if (count_split(command) > 1)
	{
		while (command[iter] && ft_is_exact(command[iter], "-n",
				ft_strlen(command[iter])) == 0)
		{
			iter++;
			n++;
		}
		while (command[iter])
		{
			printf("%s", command[iter]);
			iter++;
			if (command[iter])
				printf(" ");
		}
	}
	if (n == 0)
		printf("\n");
}
