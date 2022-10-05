/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samoreno <samoreno@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 08:57:57 by samoreno          #+#    #+#             */
/*   Updated: 2022/08/05 20:10:46 by samoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_pwd(t_list **env, t_comm *comm)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		exitfree(comm, print_error(-1, "pwd: "), *env);
	printf("%s\n", pwd);
	free(pwd);
	check_status(0, env, comm);
	return (0);
}

int	ft_env(char **command, t_list *env)
{
	int	i;

	i = count_split(command);
	if (i != 1)
	{
		print_error(22, "env");
		return (1);
	}
	else
	{
		if (env)
			ft_lstiter(env, ft_printenv);
		return (1);
	}
}

//export outils

void	copy_export(char *value, char *comm)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (ft_strchr(comm, '$'))
		value[i++] = 3;
	while (comm[j])
	{
		if (comm[j] == '"')
			value[i] = 2;
		else if (comm[j] == '\'')
			value[i] = 1;
		else
			value[i] = comm[j];
		i++;
		j++;
	}
	if (ft_strchr(comm, '$'))
		value[i++] = 3;
	value[i] = 0;
}
