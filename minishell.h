/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samoreno <samoreno@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 09:58:21 by samoreno          #+#    #+#             */
/*   Updated: 2022/07/05 14:21:58 by samoreno         ###   ########.fr       */
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

typedef struct s_comm
{
	char	*og;
	char	*parsed;
	char	**piped;
}	t_comm;

//Funciones relacionadas con el env
t_list	*envlist(char **envp);
void	delcontent(void *content);
t_dict	*dict(char *envp);
//Funciones relacionadas con exit e impresión de errores
int		print_error(int code);
void	ft_free(char **array, int words);
void	exitfree(char **split, int status, t_list *env);
void	ft_exit(char **command, t_list *env);
//Funciones útiles en distintos casos
int		is_equal(char *str);
int		is_number(char *str);
int		count_split(char **split);
void	ft_delcontent(void *content);
void	ft_delcopy(void *content);
void	ft_printenv(void *env);
void	*ft_placeholder(void *content);
int		ft_is_exact(const char *src, const char *search, size_t n);
int		ft_vars(char **command);
int		ft_isequal(char *str);
//Funciones del parser
void	parser(char *read, t_list *env);
int		closed_quotes(char *read);
char	**same_quote(char *line, char qt);
int		count_quoted(char *read, t_list *env);
int		check_value(char *var, char *env, size_t n, size_t k);
int		count_dqt_dollar(char *read, size_t i, t_list *env);
int		fill_dq_dollar(char *read, char *unquoted, int i, t_list *env);
int		find_fill(char *read, char *unquoted, size_t i, t_list *env);
int		count_dq(char *read, int i, int j, t_list *env);
//Funciones relacionadas con comandos builtin
void	ft_cd(char **command, t_list *env);
int		ft_pwd(int count);
void	ft_env(char **command, t_list *env);
void	ft_echo(char **command, t_list *env);
int		ft_declared(char *comm);
void	ft_order(t_list *env);
void	ft_export(char **command, t_list *env);
void	ft_used(char **comm, int seen);
void	ft_unset(char **command, t_list *env);
//Funciones relacionadas con ejecutar comandos
void	ft_simple(t_comm *comm, t_list *env);
#endif