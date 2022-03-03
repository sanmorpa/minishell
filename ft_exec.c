/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josuna-t <josuna-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 15:05:20 by josuna-t          #+#    #+#             */
/*   Updated: 2022/02/24 15:22:35 by josuna-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct s_pipe
{
	int		cid1;
	char	**parg[2];
	int		pipefd[2];
	int		error;
}	t_pipe;

char	*checkpath(char **parg, char *env)
{
	char		*tmpdir[2];
	int			index;
	int			fd;
	char		**pdirs;

	pdirs = ft_split(&env[5], ':');
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
	ft_free(pdirs, ft_count_split(pdirs));
	if (fd >= 0)
	{	
		execve(tmpdir[1], parg, NULL);
	}
	else
		free(tmpdir[1]);
	return (0);
}

int	redirection(char redchar, char *path)
{
	int		fd;
	int		perm;
	int		fdred;

	fdred = 0;
	if (redchar == '>')
	{
		perm = O_RDWR | O_CREAT | O_TRUNC;
		fdred = 1;
	}
	else
		perm = O_RDONLY;
	fd = open(path, perm, 0666);
	if (fd < 0)
	{	
		perror("open");
		return (1);
	}
	dup2(fd, fdred);
	close (fd);
	return (0);
}

int	checkfiles(t_pipe *vars, char *string, int fdin, int fdout)
{
	int		index;
	int		eindex;

	vars->error = 0;
	vars->parg[0] = ft_split(string, ' ');
	index = 0;
	eindex = -1;
	dup2(fdin, 0);
	if (fdin != 0)
		close (fdin);
	dup2(fdout, 1);
	if (fdout != 1)
		close(fdout);
	while (vars->parg[0][index] != 0)
	{
		if ((vars->parg[0][index][0] == '<') || (vars->parg[0][index][0] == '>'))
		{
			redirection(vars->parg[0][index][0], vars->parg[0][index + 1]);
			vars->parg[0][index] = NULL;
			vars->parg[0][++index] = NULL;
		}
		else
		{
			if (eindex < 0)
				eindex = index;
		}
		index++;
	}
	if (vars->parg[0][eindex][0] == '.' || vars->parg[0][eindex][0] == '/')
		execve(vars->parg[0][eindex], &vars->parg[0][eindex], NULL);
	else
		checkpath(vars->parg[0], getenv("PATH"));
	perror(vars->parg[0][eindex]);
	exit (0);
	return (1);
}	

int	ft_exec(char **commands)
{
	int		count;
	t_pipe	vars;
	int	temppipe;

	vars.pipefd[0] = 0;
	count = 0;
	while (commands[count] != 0)
	{
		if (commands[count + 1] != 0)
			pipe(vars.pipefd);
		printf("1 pipe 0 %d\n", vars.pipefd[0]);
		if (count > 0)
			vars.pipefd[0] = temppipe;
		printf("2 pipe 0 %d\n", vars.pipefd[0]);
		vars.cid1 = fork();
		if (vars.cid1 == 0)
		{	
			if (count == 0 && commands[count + 1] != 0)
				checkfiles(&vars, commands[count], 0, vars.pipefd[1]);
			else if (count == 0 && commands[count + 1] == 0)
				checkfiles(&vars, commands[count], 0, 1);
			else if (count > 0 && commands[count + 1] == 0)
				checkfiles(&vars, commands[count], vars.pipefd[0], 1);
			else
				checkfiles(&vars, commands[count], vars.pipefd[0], vars.pipefd[1]);
		}
		temppipe = vars.pipefd[0];
		close(vars.pipefd[1]);
		wait(0);
		count++;
		printf("Valor de count %d\n", count);
	}
	return (0);
}
