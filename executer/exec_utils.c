/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josuna-t <josuna-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 15:27:22 by josuna-t          #+#    #+#             */
/*   Updated: 2022/08/08 17:36:32 by josuna-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static	int	ft_redinput(char *redirection)
{
	int		fd;
	int		var;

	var = 1;
	if (redirection[1] != '>')
		fd = open(&redirection[1], O_RDWR | O_CREAT | O_TRUNC, 0666);
	else if (redirection[1] == '<')
		fd = open(&redirection[++var], O_RDWR | O_CREAT | O_TRUNC, 0666);
	else
		fd = open(&redirection[++var], O_RDWR | O_CREAT | O_APPEND, 0666);
	if (fd < 0)
	{	
		perror(&redirection[var]);
		return (1);
	}
	dup2(fd, 1);
	close(fd);
	return (0);
}

static	int	ft_redoutput(char *redirection)
{
	int		fd;
	int		var;

	var = 1;
	if (redirection[1] == '>')
		fd = open(&redirection[++var], O_RDONLY, 0222);
	else
		fd = open(&redirection[1], O_RDONLY, 0222);
	if (fd < 0)
	{	
		perror(&redirection[var]);
		return (1);
	}
	dup2(fd, 0);
	close(fd);
	return (0);
}

int	ft_redirect(t_element *c)
{
	int		i;

	i = 0;
	while (c->redirects[i] != 0)
	{
		if (c->redirects[i + 1] && (!ft_strchr(c->redirects[i + 1], '>')
				&& !ft_strchr(c->redirects[i + 1], '<')))
		{
			printf("Ambiguous redirection\n");
			exit (1);
		}
		if (c->redirects[i][0] == '>')
		{
			if (ft_redinput(c->redirects[i]) != 0)
				return (1);
		}
		else if (c->redirects[i][0] == '<')
		{
			if (ft_redoutput(c->redirects[i]) != 0)
				return (1);
		}
		i++;
	}
	return (0);
}

int	findpath(char **env)
{
	int	index;

	index = 0;
	while (env[index] != 0)
	{
		if (ft_strncmp("PATH=", env[index], 5) == 0)
			return (index);
		index++;
	}
	return (0);
}

char	*checkpath(char **parg, char **env)
{
	char		*tmpdir[2];
	int			index;
	int			fd;
	char		**pdirs;

	index = findpath(env);
	pdirs = ft_split(env[index], ':');
	index = 0;
	fd = -1;
	while (pdirs[index] != 0 && fd < 0)
	{
		if (index > 0)
			free(tmpdir[1]);
		tmpdir[0] = ft_strjoin(pdirs[index++], "/");
		tmpdir[1] = ft_strjoin(tmpdir[0], parg[0]);
		free(tmpdir[0]);
		fd = access(tmpdir[1], F_OK);
	}
	ft_free(pdirs, count_split(pdirs));
	if (fd >= 0)
		return (tmpdir[1]);
	else
		free(tmpdir[1]);
	return (0);
}
