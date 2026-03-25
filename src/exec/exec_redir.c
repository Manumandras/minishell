/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmittelb <mmittelb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 13:41:12 by mmittelb          #+#    #+#             */
/*   Updated: 2025/12/10 11:34:36 by mmittelb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "expansions.h"
#include "utils.h"

static int	handle_redir_in(t_general *general, t_redir *redirs)
{
	int	fd;

	fd = open(redirs->filename, O_RDONLY);
	if (open_check(general, fd, redirs->filename) != 0)
		return (1);
	if (dup2_wrapper(general, fd, 0) != 0)
	{
		ft_close(fd);
		return (1);
	}
	ft_close(fd);
	return (0);
}

static int	handle_redir_out_or_append(t_general *general, t_redir *redirs)
{
	int	fd;

	if (redirs->type == REDIR_APPEND)
	{
		fd = open(redirs->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (open_check(general, fd, redirs->filename) != 0)
			return (1);
		if (dup2_wrapper(general, fd, 1) != 0)
			return (ft_close(fd), 1);
		ft_close(fd);
	}
	if (redirs->type == REDIR_OUT)
	{
		fd = open(redirs->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (open_check(general, fd, redirs->filename) != 0)
			return (1);
		if (dup2_wrapper(general, fd, 1) != 0)
			return (ft_close(fd), 1);
		ft_close(fd);
	}
	return (0);
}

static int	check_filename_and_expand(t_general *general, \
	t_redir *redir, int pid_flag)
{
	char	*temp[2];
	char	**expanded_redir;

	if (filename_check(general, redir, pid_flag) != 0)
		return (general->exit_status);
	temp[0] = redir->filename;
	temp[1] = NULL;
	expanded_redir = expand_argv(general, temp);
	if (!expanded_redir || expanded_redir[1] != NULL || \
		expanded_redir[0][0] == '\0')
	{
		write3(general, "minishell: ", \
			redir->filename, ": ambiguous redirect\n");
		if (pid_flag == 0)
			exit_with_status_and_cleanup(general, 1);
		general->exit_status = 1;
		return (general->exit_status);
	}
	redir->filename = expanded_redir[0];
	return (0);
}

static int	handle_single_redirection(t_general *general, \
	t_redir *redir, int pid_flag)
{
	int	ret;

	if (redir->type != REDIR_HEREDOC)
	{
		ret = check_filename_and_expand(general, redir, pid_flag);
		if (ret != 0)
			return (ret);
	}
	if (redir->type == REDIR_IN)
	{
		if (handle_redir_in(general, redir) != 0)
			return (1);
	}
	if (redir->type == REDIR_OUT || redir->type == REDIR_APPEND)
	{
		if (handle_redir_out_or_append(general, redir) != 0)
			return (1);
	}
	if (redir->type == REDIR_HEREDOC)
	{
		if (apply_redir_heredoc(general, redir) != 0)
			return (1);
	}
	return (0);
}

int	handle_redirections(t_general *general, t_redir *redir, int pid_flag)
{
	int	ret;

	while (redir)
	{
		ret = handle_single_redirection(general, redir, pid_flag);
		if (ret != 0)
			return (ret);
		redir = redir->next;
	}
	return (0);
}
