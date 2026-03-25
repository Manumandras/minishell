/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmittelb <mmittelb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 16:22:40 by jnieders          #+#    #+#             */
/*   Updated: 2025/12/10 11:33:36 by mmittelb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "minishell.h"

void	free_str_arr(char **str_arr);
int		count_args(char **argv);
int		print_getcwd_error(void);
char	**skip_quotes_and_split(t_general *general, char *s, char c);
int		skip_quotes(char *line, int i, int c);
int		ft_create_pipe(t_general *general, int pipe_fd[2]);
int		set_exitstatus(int status, t_general *general);
int		dup2_wrapper(t_general *general, int fd1, int fd2);
void	handler(int signum);
void	ft_close(int fd);
int		ft_create_pipe(t_general *general, int pipe_fd[2]);
void	signal_check(t_general *general);
void	exit_with_status_and_cleanup(t_general *general, int exitstatus);
void	setup_signals(void);
void	end_of_line_check(t_general *general, char *line);
int		handle_child_status(t_general *general, int status,
			char **trimmed_line, int fd_read);
void	close_open_fds(t_ast *node);
char	*write3(t_general *general, const char *a,
			const char *b, const char *c);
void	error_with_errno(t_general *general, const char *prefix,
			const char *name);

#endif
