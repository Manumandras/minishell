/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmittelb <mmittelb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 17:47:41 by mmittelb          #+#    #+#             */
/*   Updated: 2025/12/10 11:35:10 by mmittelb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "utils.h"

void	close_fds(int *fd)
{
	ft_close(fd[0]);
	ft_close(fd[1]);
}

int	restore_stdio(t_general *general, int saved_fd[2])
{
	if (dup2_wrapper(general, saved_fd[0], 0) != 0)
	{
		close_fds(saved_fd);
		reset_fds(general);
		return (1);
	}
	if (dup2_wrapper(general, saved_fd[1], 1) != 0)
	{
		close_fds(saved_fd);
		reset_fds(general);
		return (1);
	}
	close_fds(saved_fd);
	reset_fds(general);
	return (0);
}

int	filename_check(t_general *general, t_redir *redir, int pid_flag)
{
	if (*redir->filename == '\0' || \
	(redir->filename[0] == '"' && redir->filename[1] == '"') \
	|| (redir->filename[0] == '\'' && redir->filename[1] == '\''))
	{
		write(2, "minishell: : No such file or directory\n", 39);
		if (pid_flag == 0)
			exit_with_status_and_cleanup(general, 1);
		general->exit_status = 1;
		return (general->exit_status);
	}
	return (0);
}

int	open_check(t_general *general, int fd_input, char *filename)
{
	if (fd_input == -1)
	{
		general->exit_status = 1;
		error_with_errno(general, "minishell: ", filename);
		close (fd_input);
		return (1);
	}
	return (0);
}

int	ft_fork(t_general *general)
{
	int	pid;

	pid = fork();
	if (pid == -1)
	{
		error_with_errno(general, "minishell: fork", "");
		general->exit_status = 1;
		return (-1);
	}
	return (pid);
}
