/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samoreno <samoreno@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 11:15:50 by samoreno          #+#    #+#             */
/*   Updated: 2022/08/05 19:38:53 by samoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	is_n_flag(char *command);

void	ft_echo(char **command, t_list *env)
{
	size_t	n;
	int		iter;

	iter = 1;
	n = 0;
	(void)env;
	if (count_split(command) > 1)
	{
		while (command[iter] && is_n_flag(command[iter]) == 0)
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
	exit (0);
}

static int	is_n_flag(char *command)
{
	int	i;

	i = 1;
	if (command[0] && command[0] == '-')
	{
		while (command[i])
		{
			if (command[i] == 'n')
				i++;
			else
				return (1);
		}
		return (0);
	}
	return (1);
}
