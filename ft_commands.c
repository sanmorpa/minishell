/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_commands.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samoreno <samoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 08:57:57 by samoreno          #+#    #+#             */
/*   Updated: 2022/03/03 10:10:09 by samoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(int count)
{
	char	*pwd;

	if (count == 1)
	{
		pwd = getcwd(NULL, 0);
		if (!pwd)
		{
			perror("getcwd");
			return (1);
		}
		printf("%s\n", pwd);
		free(pwd);
	}
	else
		printf("pwd: too many arguments\n");
	return (0);
}

void	ft_exit(char **command, t_list *env)
{
	printf("exit\n");
	if (ft_count_split(command) == 1)
		ft_exitfree(command, 0, env);
	if (ft_is_number(command[1]) == 1)
		ft_exitfree(command, 255, env);
	ft_exitfree(command, ft_atoi(command[1]) % 256, env);
	ft_exitfree(command, ft_atoi(command[1]), env);
}

void	ft_env(char **command, t_list *env)
{
	int	i;

	i = ft_count_split(command);
	if (i != 1)
		printf("Error: invalid syntax\n");
	else
	{
		if (env)
			ft_lstiter(env, ft_printenv);
	}
}
