/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_aux.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josuna-t <josuna-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 11:09:11 by samoreno          #+#    #+#             */
/*   Updated: 2022/08/08 17:41:30 by josuna-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	export_error(char **command, int iter)
{
	if (command[iter][0])
	{
		ft_putstr_fd("minishell: export: ", 2);
		print_error(22, command[iter]);
		command[iter][0] = 0;
	}
	return (1);
}

int	replace_export(char *comm, int e, t_dict *el)
{
	free(el->value);
	if (ft_strchr(comm, '$'))
		el->value = malloc(sizeof(char)
				* (ft_strlen(comm) - e + 3));
	else
		el->value = malloc(sizeof(char)
				* (ft_strlen(comm) - e + 1));
	if (!el->value)
		return (2);
	comm += e + 1;
	copy_export(el->value, comm);
	return (0);
}

void	print_export_values(t_dict *el)
{
	size_t	i;

	i = 0;
	printf("=\"");
	if (ft_strchr(el->value, '$'))
		i++;
	while (el->value[i] || (ft_strchr(el->value, '$')
			&& i < ft_strlen(el->value) - 1))
	{
		if (el->value[i] == '$')
			printf("\\");
		if (el->value[i] == 1)
			printf("'");
		if (el->value[i] == 2)
			printf("\"");
		if (el->value[i] != 1 && el->value[i] != 2
			&& el->value[i] != 3)
			printf("%c", el->value[i]);
		i++;
	}
	printf("\"");
}

int	first_check_export(int iter, char **command)
{
	if (iter >= 1 && command[1][0] == 0)
	{
		print_error(22, "minishell: export");
		return (1);
	}
	return (0);
}
