/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samoreno <samoreno@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 12:18:21 by samoreno          #+#    #+#             */
/*   Updated: 2022/07/05 11:56:20 by samoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free(char **array, int words)
{
	int	iter;

	iter = 0;
	while (iter < words)
	{
		free(array[iter]);
		iter++;
	}
	free(array);
}

void	exitfree(char **split, int status, t_list *env)
{
	if (split)
		ft_free(split, count_split(split));
	ft_lstclear(&env, delcontent);
	exit(status);
}

void	ft_exit(char **command, t_list *env)
{
	printf("exit\n");
	if (command)
	{
		if (count_split(command) == 1)
			exitfree(command, 0, env);
		if (is_number(command[1]) == 1)
			exitfree(command, 255, env);
		exitfree(command, ft_atoi(command[1]) % 256, env);
	}
	exit(1);
}

int	print_error(int code)
{
	int	error;

	if (code > 0)
		errno = code;
	perror("Error");
	error = errno;
	errno = 0;
	return (error);
}

/* Códigos de error para poner errno:
https://www.thegeekstuff.com/2010/10/linux-error-codes/ */