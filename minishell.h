/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josuna-t <josuna-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 09:58:21 by samoreno          #+#    #+#             */
/*   Updated: 2022/08/09 18:12:44 by josuna-t         ###   ########.fr       */
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

typedef struct s_element
{
	char	*original;
	char	**command;
	char	**redirects;
}	t_element;

typedef struct s_comm
{
	char	*og;
	t_list	*redirections;
}	t_comm;

typedef struct s_signal
{
	int					cid1;
	int					s_flag;
	struct sigaction	parent_action;
	struct sigaction	child_action;
	struct sigaction	ctrl_slash;
	struct termios		termios_new;
	struct termios		termios_old;
}	t_signal;

//Funciones relacionadas con el env
t_list		*envlist(char **envp);
char		**ft_lsttostring(t_list *lst);
void		delcontent(void *content);
t_dict		*dict(char *envp);
void		fill_value_dict(size_t e, t_dict *entry, char *envp);
//Funciones relacionadas con exit e impresión de errores
int			print_error(int code, char *error);
void		ft_free(char **array, int words);
void		exitfree(t_comm *command, int status, t_list *env);
int			ft_exit(char **command, t_comm *comm, t_list *env, int child);
void		cleanexit(t_list *env, t_element *element);
//Funciones útiles en distintos casos
int			is_equal(char *str);
int			is_number(char *str);
int			count_split(char **split);
void		ft_delcontent(void *content);
void		ft_delcopy(void *content);
void		ft_printenv(void *env);
void		*ft_placeholder(void *content);
int			ft_is_exact(const char *src, const char *search, size_t n,
				int comm);
int			ft_vars(char *command);
int			ft_isequal(char *str);
int			ft_replace(char *comm, t_list *env);
void		clear_commands(void *comm);
int			is_equal_unset(char *str);
//Funciones del parser
void		parser(char *read, t_list **env);
int			closed_quotes(char *read);
char		**same_quote(char *line, char qt);
int			count_quoted(char *read, t_list *env, int _l_flag);
int			check_value(char *var, char *env, size_t n, size_t k);
int			count_dqt_dollar(char *read, size_t i, t_list *env);
int			fill_dq_dollar(char *read, char *unquoted, int i, t_list *env);
int			find_fill(char *read, char *unquoted, size_t i, t_list *env);
int			count_dq(char *read, int i, int j, t_list *env);
void		fill_dollar_nqt(char *read, char *unquoted, t_list *env, int i[2]);
char		**ft_split_og(char const *s, char c);
char		*without_quotes(char *read, t_list *env, int l_flag);
void		quote_redirect(int i[2], char *unquoted, char *read, char redirect);
int			check_redirect(int i, char *read, char redirect);
t_list		*command_list(char *original, t_list *env);
char		**fill_command_comm(char *original, t_list *env, t_element *el);
char		**fill_command_red(char *original, t_list *env, t_element *elm);
int			fill_command(t_list *comm);
char		*filehere(char *redirection, int size, t_list *env, t_element *el);
char		*count_fill_heredoc(char *r, t_list *env);
char		*checkered(char *red, int *quoted, t_list *env, t_element *element);
void		simple_quote_no_last(char *read, int i[2]);
int			is_there_redirections(char *original);
int			open_quotes(char now, int quotes);
void		fill_dqs(int i[2], char *unquoted, t_list *env, char *read);
void		sq_no_flag(char *unquoted, char *read, int i[2]);
char		**split_commands(char **command);
int			ft_count_words(char const *s, char c);
char		**dollars_command(char *com, t_list *env, int i, t_element *elm);
int			find_dollars_aux(int qt, int i, char *el);
int			aux_fill_words(char **array, size_t word_c, char *temp);
int			check_pipes(char *read);
void		fill_find_fill(char *unquoted, char *read);
void		clean_tabs(char *command);
int			check_reds(char *read);
//Funciones relacionadas con comandos builtin
int			ft_cd(char **command, t_comm *comm, t_list *env);
int			ft_pwd(t_list **env, t_comm *comm);
int			ft_env(char **command, t_list *env);
void		ft_echo(char **command, t_list *env);
int			ft_declared(char *comm);
void		ft_order(t_list *env);
int			ft_export(char **command, t_comm *comm, t_list *env, int iter);
void		ft_used(char **comm, int seen);
int			ft_unset(char **command, t_list **env);
void		copy_export(char *value, char *comm);
int			export_error(char **command, int iter);
int			replace_export(char *comm, int e, t_dict *el);
void		print_export_values(t_dict *el);
int			first_check_export(int iter, char **command);
//Funciones relacionadas con ejecutar comandos, reedirecciones, pipes
void		ft_exec(t_comm comm, t_list **env);
void		check_status(int status, t_list **env, t_comm *comm);
void		ft_simple(t_element *command, t_list **env, t_comm *comm);
int			ft_redirect(t_element *command);
char		*checkpath(char **parg, char **env);
int			waitallchilds(int *cids, int count);
int			f_redirections(t_comm comm, t_list **env, int *cids, int *pipefd);
//Funciones relacionadas con señales
void		sig_handler_parent(int signum);
int			ctrld_handler(t_list *env);
void		fill_sigactions(void);
void		print_signal(t_signal *sigactions);
void		sig_handler_child(int signum);

#endif
