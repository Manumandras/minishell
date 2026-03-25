/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_unit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmittelb <mmittelb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 14:03:53 by mmittelb          #+#    #+#             */
/*   Updated: 2025/12/11 13:11:33 by mmittelb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "libft.h"
#include "expansions.h"
#include "utils.h"

static int	save_parent_stdio(t_general *general, int saved_fd[2])
{
	saved_fd[0] = dup(0);
	if (saved_fd[0] == -1)
	{
		general->exit_status = 1;
		return (1);
	}
	saved_fd[1] = dup(1);
	if (saved_fd[1] == -1)
	{
		ft_close(saved_fd[0]);
		general->saved_fd[0] = -1;
		general->exit_status = 1;
		return (1);
	}
	general->saved_fd[0] = saved_fd[0];
	general->saved_fd[1] = saved_fd[1];
	return (0);
}

static int	exec_cmd_unit_parent(char **argv,
				t_redir *redirs, t_general *general)
{
	int	status;
	int	saved_fd[2];

	if (save_parent_stdio(general, saved_fd) != 0)
		return (1);
	argv = expand_argv(general, argv);
	status = exec_builtins(general, argv, redirs, 1);
	if (status >= 0)
	{
		if (restore_stdio(general, saved_fd) != 0)
			return (1);
		general->exit_status = status;
		return (status);
	}
	if (status == -2)
	{
		if (restore_stdio(general, saved_fd) != 0)
			return (1);
		return (general->exit_status);
	}
	close_fds(saved_fd);
	reset_fds(general);
	if (!argv && !redirs)
		return (0);
	return (execute_bash_cmd(general, redirs, argv));
}

static void	exec_cmd_unit_child(char **argv,
				t_redir *redirs, t_general *general)
{
	int	status;

	argv = expand_argv(general, argv);
	if (!argv)
		exit_with_status_and_cleanup(general, 0);
	status = exec_builtins(general, argv, redirs, 0);
	if (status >= 0)
		exit_with_status_and_cleanup(general, status);
	if (status == -2)
		exit_with_status_and_cleanup(general, general->exit_status);
	status = execute_bash_cmd(general, redirs, argv);
	exit_with_status_and_cleanup(general, status);
}

int	exec_cmd_unit(char **argv, t_redir *redirs,
			t_general *general, int in_child)
{
	if (in_child == 1)
	{
		exec_cmd_unit_child(argv, redirs, general);
		return (general->exit_status);
	}
	return (exec_cmd_unit_parent(argv, redirs, general));
}
