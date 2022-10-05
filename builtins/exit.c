/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josuna-t <josuna-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 12:18:21 by samoreno          #+#    #+#             */
/*   Updated: 2022/08/09 18:11:53 by josuna-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern t_signal	g_signal;

void	ft_free(char **array, int words)
{
	int	iter;

	iter = 0;
	while (iter < words)
	{
		if (array[iter])
			free(array[iter]);
		iter++;
	}
	if (array)
		free(array);
}

void	exitfree(t_comm *command, int status, t_list *env)
{
	if (command)
	{
		if (command->og)
			free(command->og);
		if (command->redirections)
			ft_lstclear(&command->redirections, clear_commands);
	}
	ft_lstclear(&env, delcontent);
	rl_clear_history();
	exit(status);
}

int	ft_exit(char **command, t_comm *comm, t_list *env, int child)
{
	if (count_split(command) > 2)
	{
		print_error(22, "exit");
		if (child == 1)
			exitfree(comm, ft_atoi(command[1]) % 256, env);
		return (1);
	}
	if (child == 0)
		printf("exit\n");
	if (count_split(command) == 1)
		exitfree(comm, 0, env);
	if (!(is_number(command[1]) != 1
			|| (command[1][0] == '-' && is_number(&command[1][1]) != 1)))
	{
		ft_putstr_fd("exit: ", 2);
		ft_putstr_fd(command[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		exitfree(comm, 255, env);
	}
	exitfree(comm, ft_atoi(command[1]) % 256, env);
	exit (0);
}

int	print_error(int code, char *errormsg)
{
	int	error;

	if (code > 0)
		errno = code;
	perror(errormsg);
	error = errno;
	errno = 0;
	return (error);
}

/* Códigos de error para poner errno:
https://www.thegeekstuff.com/2010/10/linux-error-codes/ */
