/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josuna-t <josuna-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 13:57:48 by josuna-t          #+#    #+#             */
/*   Updated: 2022/08/08 17:16:48 by josuna-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern t_signal	g_signal;

void	cleanexit(t_list *env, t_element *element)
{
	clear_commands((void *)element);
	exitfree(0, -1, env);
}

int	createfile(char **redirection)
{
	int		fd;
	char	*read;
	char	*path;
	int		index;

	index = 0;
	fd = -1;
	while (fd < 0)
	{
		read = ft_itoa(index++);
		if (read == 0)
			return (-1);
		path = ft_strjoin("</tmp/.heredoc", read);
		if (path == 0)
			return (-1);
		free(read);
		fd = open(&path[1], O_RDWR | O_CREAT | O_EXCL, 0666);
		if (fd < 0)
			free(path);
	}
	free(*redirection);
	*redirection = path;
	return (fd);
}

static	void	*checkread(char *read, t_list *env, int fd, int expand)
{
	if (ft_strchr(read, '$') && expand == 0)
		read = count_fill_heredoc(read, env);
	if (!read)
		return (NULL);
	write(fd, read, ft_strlen(read));
	write(fd, "\n", 1);
	free(read);
	return (read);
}

char	*filehere(char *red, int s, t_list *env, t_element *element)
{
	char	*read;
	int		fd;
	int		expand;
	char	*chk;
	int		stdincopy;

	stdincopy = dup(STDIN_FILENO);
	expand = 0;
	chk = checkered(&red[3], &expand, env, element);
	fd = createfile(&red);
	g_signal.cid1 = -2;
	read = readline("> ");
	while (read != 0 && ft_is_exact(chk, read, s, 1) == 1)
	{
		read = checkread(read, env, fd, expand);
		if (!read)
			cleanexit(env, element);
		read = readline("> ");
	}
	g_signal.cid1 = 1;
	dup2(stdincopy, STDIN_FILENO);
	free(read);
	free(chk);
	close(fd);
	return (red);
}
