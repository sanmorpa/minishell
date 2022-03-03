/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samoreno <samoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 16:16:46 by samoreno          #+#    #+#             */
/*   Updated: 2022/03/01 13:34:36 by samoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <curses.h>
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h> 
# include <term.h>
# include <termios.h>
# include <unistd.h>
# include "./libft/libft.h"

typedef struct s_dict
{
	char	*key;
	char	*value;
}	t_dict;

int		ft_check(char *str, t_list *env);
t_list	*ft_envlist(char **envp);
void	ft_free(char **array, int words);
void	ft_exitfree(char **split, int status, t_list *env);
int		ft_is_exact(const char *src, const char *search, size_t n);
int		ft_count_split(char **split);
int		ft_pwd(int count);
void	ft_env(char **command, t_list *env);
void	ft_exit(char **command, t_list *env);
void	ft_export(char **command, t_list *env);
int		ft_is_number(char *str);
void	ft_isenv(char *env, char **comm);
int		ft_exec(char **commands);
int		ft_vars(char **command);
int		ft_isequal(char *str);
void	ft_delcontent(void *content);
void	ft_printenv(void *env);
t_dict	*ft_dict(char *envp);
void	*ft_placeholder(void *content);
void	ft_delcopy(void *content);
void	ft_order(t_list *env);
void	ft_unset(char **command, t_list *env);
void	ft_used(char **comm, int seen);

#endif
