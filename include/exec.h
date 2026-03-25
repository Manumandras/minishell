/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmittelb <mmittelb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 14:55:52 by jnieders          #+#    #+#             */
/*   Updated: 2025/12/10 12:45:36 by mmittelb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "minishell.h"
# include "parse.h"

typedef enum e_export_mode
{
	EXP_PLAIN,
	EXP_ASSIGN,
	EXP_APPEND,
	EXP_ERROR
}	t_export_mode;

typedef struct s_export_arg
{
	t_export_mode	mode;
	char			*key;
	char			*value;
}	t_export_arg;

/* ============================= Builtins ============================== */

int		exec_builtins(t_general *general, char **argv, \
	t_redir *redirs, int pid_f);
int		builtin_shell_vars(t_general *general, char **argv);
int		builtin_echo(char **argv);
int		builtin_cd(t_general *general, char **argv);
int		builtin_pwd(void);
int		builtin_export(t_general *general, char **argv);
int		builtin_unset(t_general *general, char **argv);
int		builtin_env(t_general *general, char **argv);
int		builtin_exit(t_general *general, char **argv);
void	print_sorted_export_list(t_general *general);
void	identify_exp_mode(t_general *general, char *arg, t_export_arg *exp);

/* =========================== Execution ============================= */

int		exec_node(t_ast *node, t_general *general, int in_child);
int		open_check(t_general *general, int fd_input, char *filename);
int		filename_check(t_general *general, t_redir *redir, int pid_flag);
int		handle_redirections(t_general *general, t_redir *redir, int pid_flag);
int		collect_heredocs(t_general *general, t_ast *node);
int		exec_pipe(t_ast *left, t_ast *right, t_general *general);
int		ft_fork(t_general *general);
int		exec_cmd_unit(char **argv, t_redir *redirs, \
	t_general *general, int in_child);
int		restore_stdio(t_general *general, int saved_fd[2]);
int		execute_bash_cmd(t_general *general, t_redir *redirs, char **argv);
void	exit_command_not_found(t_general *general, char *cmd);
void	exit_permission_denied(t_general *general, char *cmd);
void	exit_no_such_file(t_general *general, char *cmd);
int		exec(t_ast *node, t_general *general);
int		apply_redir_heredoc(t_general *general, t_redir *redir);
void	close_fds(int *fd);
void	reset_fds(t_general *general);

#endif
