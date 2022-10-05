/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samoreno <samoreno@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 09:35:52 by samoreno          #+#    #+#             */
/*   Updated: 2022/08/08 12:48:10 by samoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//static char	**piped_parsed(t_list *env, t_comm *comm);

static int	check_alone(t_element *elements, t_comm *comm, t_list **env)
{
	if (comm->redirections->next == 0 && elements->command[0])
	{
		if (ft_is_exact(elements->command[0], "exit", 4, 1) == 0)
			check_status(ft_exit(elements->command, comm, *env, 0), env, comm);
		else if (ft_is_exact(elements->command[0], "cd", 2, 1) == 0)
			check_status(ft_cd(elements->command, comm, *env), env, comm);
		else if (ft_is_exact(elements->command[0], "export", 6, 1) == 0)
			check_status(ft_export(elements->command, comm, *env,
					count_split(elements->command) - 1), env, comm);
		else if (ft_is_exact(elements->command[0], "unset", 5, 1) == 0)
			check_status(ft_unset(elements->command, env), env, comm);
		else
			return (0);
	}
	else
		return (0);
	return (1);
}

void	parser(char *line, t_list **env)
{
	t_comm	comm;
	int		rch;

	if (closed_quotes(line) == 1 || (ft_strlen(line) == 1 && line[0] == '|'))
		ft_putstr_fd("minishell: syntax error\n", 2);
	else
	{
		comm.og = line;
		comm.redirections = command_list(line, *env);
		if (!comm.redirections)
			exitfree(&comm, print_error(-1, "error"), *env);
		rch = check_alone((t_element *)comm.redirections->content, &comm, env);
		if (rch == 0)
			ft_exec(comm, env);
		ft_lstclear(&comm.redirections, clear_commands);
	}
}

int	check_redirect(int i, char *read, char redirect)
{
	i++;
	if (read[i])
	{
		if (read[i] && read[i] != redirect)
		{
			if ((redirect == '<' && read[i] == '>')
				|| (redirect == '>' && read[i] == '<'))
				return (-1);
			else
				return (i - 1);
		}
		if (read[i + 1])
		{
			if (read[i + 1] != redirect && ((redirect == '<'
						&& read[i + 1] != '>') || (redirect == '>'
						&& read[i + 1] != '<')))
				return (i);
			return (-1);
		}
		return (i);
	}
	return (-1);
}

void	simple_quote_no_last(char *read, int i[2])
{
	i[1] += 2;
	i[0]++;
	while (read[i[0]] && (read[i[0]] != '\''))
	{
		i[1]++;
		i[0]++;
	}
	i[0]++;
}
