/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samoreno <samoreno@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 08:57:57 by samoreno          #+#    #+#             */
/*   Updated: 2022/07/04 09:41:53 by samoreno         ###   ########.fr       */
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

void	ft_env(char **command, t_list *env)
{
	int	i;

	i = count_split(command);
	if (i != 1)
		printf("Error: invalid syntax\n");
	else
	{
		if (env)
			ft_lstiter(env, ft_printenv);
	}
}
