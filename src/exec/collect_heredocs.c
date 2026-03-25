/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collect_heredocs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmittelb <mmittelb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 13:01:17 by mmittelb          #+#    #+#             */
/*   Updated: 2025/12/11 13:20:12 by mmittelb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "libft.h"
#include "expansions.h"
#include "utils.h"

static void	check_expansion_need(t_redir *redir)
{
	int	i;

	i = 0;
	redir->expanded = true;
	while (redir->delimiter[i])
	{
		if (redir->delimiter[i] == '\'' || redir->delimiter[i] == '"')
		{
			redir->expanded = false;
			return ;
		}
		i++;
	}
}

static void	run_heredoc_child(t_general *general,
				t_redir *redir, int write_fd)
{
	char	*line;
	char	*line_plus_nl;
	char	*delim_plus_nl;

	redir->delimiter = remove_quotes_str(general, redir->delimiter);
	delim_plus_nl = gc_strjoin(general, redir->delimiter, "\n");
	while (1)
	{
		line = readline("> ");
		if (line == NULL)
		{
			ft_close(write_fd);
			exit_with_status_and_cleanup(general, 0);
		}
		add_in_gc(general, line);
		line_plus_nl = gc_strjoin(general, line, "\n");
		if (ft_strncmp(line_plus_nl, delim_plus_nl,
				ft_strlen(delim_plus_nl)) == 0)
		{
			ft_close(write_fd);
			exit_with_status_and_cleanup(general, 0);
		}
		write(write_fd, line_plus_nl, ft_strlen(line_plus_nl));
	}
}

static int	run_single_heredoc(t_general *general, t_redir *redir)
{
	int		fd[2];
	pid_t	pid;
	int		status;

	if (ft_create_pipe(general, fd) != 0)
		return (1);
	pid = ft_fork(general);
	if (pid < 0)
		return (close_fds(fd), 1);
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		ft_close(fd[0]);
		run_heredoc_child(general, redir, fd[1]);
	}
	signal(SIGINT, SIG_IGN);
	ft_close(fd[1]);
	waitpid(pid, &status, 0);
	if (set_exitstatus(status, general) == 1)
		return (ft_close(fd[0]), 1);
	redir->pipe_read_end = fd[0];
	return (0);
}

int	collect_heredocs(t_general *general, t_ast *node)
{
	t_redir	*tmp;

	tmp = node->redirs;
	while (tmp)
	{
		if (tmp->type == REDIR_HEREDOC)
		{
			check_expansion_need(tmp);
			if (run_single_heredoc(general, tmp) == 1)
				return (1);
		}
		tmp = tmp->next;
	}
	if (node->left && collect_heredocs(general, node->left) != 0)
		return (1);
	if (node->right && collect_heredocs(general, node->right) != 0)
		return (1);
	return (0);
}
