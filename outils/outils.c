/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josuna-t <josuna-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 11:35:34 by samoreno          #+#    #+#             */
/*   Updated: 2022/08/08 15:20:05 by josuna-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

void	clear_commands(void *comm)
{
	t_element	*el;

	el = comm;
	if (el->command)
		ft_free(el->command, count_split(el->command));
	if (el->redirects)
		ft_free(el->redirects, count_split(el->redirects));
	if (el->original)
		free(el->original);
	if (el)
		free(el);
}

int	ft_vars(char *command)
{
	size_t	iter;

	iter = 0;
	if (!command || !command[0] || ft_isdigit(command[0]) == 1)
		return (1);
	while (command[iter] && command[iter] != '=')
	{
		if (ft_isalnum(command[iter]) == 0
			&& command[iter] != '_')
			return (1);
		iter++;
	}
	if (iter == 0)
		return (1);
	return (0);
}
