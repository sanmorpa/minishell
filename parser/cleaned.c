/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaned.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josuna-t <josuna-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 10:56:50 by samoreno          #+#    #+#             */
/*   Updated: 2022/08/08 17:29:23 by josuna-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_element	*og_command(char *command, t_list *env)
{
	t_element	*el;

	el = malloc(sizeof(t_element));
	el->original = malloc(sizeof(char) * (ft_strlen(command) + 1));
	if (!el || !el->original)
	{
		if (el)
			free(el);
		return (NULL);
	}
	ft_strlcpy(el->original, command, ft_strlen(command) + 1);
	el->command = fill_command_comm(el->original, env, el);
	el->redirects = fill_command_red(el->original, env, el);
	if (!el->command || !el->redirects)
	{
		clear_commands((void *)el);
		return (NULL);
	}
	return (el);
}

static int	fill_command_list(t_list *command, char **splited, t_list *env)
{
	int			i;
	t_element	*el;

	i = 1;
	while (splited[i])
	{
		el = og_command(splited[i++], env);
		if (!el)
		{
			ft_free(splited, count_split(splited));
			ft_lstclear(&command, clear_commands);
			return (1);
		}
		ft_lstadd_back(&command, ft_lstnew((void *)el));
	}
	ft_free(splited, count_split(splited));
	return (0);
}

t_list	*command_list(char *original, t_list *env)
{
	t_list		*command;
	char		**splited;
	t_element	*el;

	splited = ft_split_og(original, '|');
	if (!splited)
		return (NULL);
	el = og_command(splited[0], env);
	if (!el->original)
	{
		ft_free(splited, count_split(splited));
		return (NULL);
	}
	command = ft_lstnew((void *)el);
	if (!command)
	{
		ft_free(splited, count_split(splited));
		clear_commands((void *)el);
		return (NULL);
	}
	if (fill_command_list(command, splited, env) == 1)
		return (NULL);
	return (command);
}

int	check_reds(char *read)
{
	int		i;
	int		c_red;
	char	reds;

	i = 0;
	c_red = 0;
	while (read[i])
	{
		if (read[i] == '>' || read[i] == '<')
		{
			reds = read[i];
			while (read[i] && read[i] == reds)
			{
				c_red++;
				i++;
			}
			if (c_red > 2)
				return (1);
		}
		if (read[i] && read[i] != ' ')
			c_red = 0;
		if (read[i])
			i++;
	}
	return (0);
}
