/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmittelb <mmittelb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 13:21:28 by mmittelb          #+#    #+#             */
/*   Updated: 2026/01/15 17:47:15 by mmittelb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "utils.h"

static void	child_right(int *fd, t_ast *right, t_general *general)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	ft_close(fd[1]);
	if (dup2_wrapper(general, fd[0], 0) != 0)
	{
		ft_close(fd[0]);
		exit_with_status_and_cleanup(general, 1);
	}
	ft_close(fd[0]);
	exec_node(right, general, 1);
	exit_with_status_and_cleanup(general, 0);
}

static void	child_left(int *fd, t_ast *left, t_general *general)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	ft_close(fd[0]);
	if (dup2_wrapper(general, fd[1], 1) != 0)
	{
		ft_close(fd[1]);
		exit_with_status_and_cleanup(general, 1);
	}
	ft_close(fd[1]);
	exec_node(left, general, 1);
	exit_with_status_and_cleanup(general, 0);
}

void	handler2(int signum)
{
	if (signum == SIGINT)
		write(1, "\n", 1);
}

int	exec_pipe(t_ast *left, t_ast *right, t_general *general)
{
	int		fd[2];
	pid_t	pid1;
	pid_t	pid2;
	int		status;

	if (ft_create_pipe(general, fd) != 0)
		return (1);
	pid1 = ft_fork(general);
	if (pid1 < 0)
		return (close_fds(fd), 1);
	if (pid1 == 0)
		child_left(fd, left, general);
	pid2 = ft_fork(general);
	if (pid2 < 0)
		return (close_fds(fd), waitpid(pid1, NULL, 0), 1);
	if (pid2 == 0)
		child_right(fd, right, general);
	signal(SIGINT, handler2);
	signal(SIGQUIT, handler2);
	close_fds(fd);
	waitpid(pid1, &status, 0);
	set_exitstatus(status, general);
	waitpid(pid2, &status, 0);
	set_exitstatus(status, general);
	return (general->exit_status);
}
