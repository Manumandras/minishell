/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_and_status.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manuelmittelbach <manuelmittelbach@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 13:06:13 by mmittelb          #+#    #+#             */
/*   Updated: 2026/03/24 19:30:36 by manuelmitte      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "parse.h"

void	ft_close(int fd)
{
	if (fd != -1)
		close(fd);
}

void	close_open_fds(t_ast *node)
{
	t_redir	*tmp;

	if (!node)
		return ;
	tmp = node->redirs;
	while (tmp)
	{
		if (tmp->pipe_read_end >= 0)
		{
			ft_close(tmp->pipe_read_end);
			tmp->pipe_read_end = -1;
		}
		tmp = tmp->next;
	}
	close_open_fds(node->left);
	close_open_fds(node->right);
}

void	exit_with_status_and_cleanup(t_general *general, int exitstatus)
{
	if (general->saved_fd[0] != -1)
		ft_close(general->saved_fd[0]);
	if (general->saved_fd[1] != -1)
		ft_close(general->saved_fd[1]);
	close_open_fds(general->ast);
	general->exit_status = exitstatus;
	gc_free_all(general);
	free_env_list(general->env);
	rl_clear_history();
	exit(exitstatus);
}

int	set_exitstatus(int status, t_general *general)
{
	int	sig;

	if (WIFEXITED(status) != 0)
	{
		general->exit_status = WEXITSTATUS(status);
		return (0);
	}
	else
	{
		sig = WTERMSIG(status);
		general->exit_status = 128 + sig;
		if (sig == SIGINT)
			write(1, "\n", 1);
		else if (sig == SIGQUIT)
			write(1, "Quit (core dumped)\n", 19);
		return (1);
	}
	return (0);
}

int	handle_child_status(t_general *general, int status,
				char **trimmed_line, int fd_read)
{
	if (WIFEXITED(status) && WEXITSTATUS(status) == 146)
	{
		ft_close(fd_read);
		exit_with_status_and_cleanup(general, 0);
	}
	if (set_exitstatus(status, general) == 1)
	{
		add_history(*trimmed_line);
		ft_close(fd_read);
		return (1);
	}
	return (0);
}
