/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmittelb <mmittelb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 14:53:03 by mmittelb          #+#    #+#             */
/*   Updated: 2025/12/10 10:46:34 by mmittelb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "expansions.h"
#include "libft.h"
#include "utils.h"

static int	read_heredoc_to_line(t_general *general, t_redir *redir,
				char **line)
{
	char	buf[2];
	int		bytes_read;

	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(redir->pipe_read_end, buf, 1);
		if (bytes_read < 0)
		{
			ft_close(redir->pipe_read_end);
			redir->pipe_read_end = -1;
			return (-1);
		}
		if (bytes_read > 0)
		{
			buf[1] = '\0';
			*line = gc_strjoin(general, *line, buf);
		}
	}
	return (0);
}

static char	*expand_heredoc(t_general *general, t_redir *redir)
{
	char	*line;
	int		dummy;

	line = NULL;
	dummy = 0;
	if (read_heredoc_to_line(general, redir, &line) < 0)
		return (NULL);
	ft_close(redir->pipe_read_end);
	redir->pipe_read_end = -1;
	return (expand_vars_in_arg(general, line, &dummy));
}

int	apply_redir_heredoc(t_general *general, t_redir *redir)
{
	char	*expanded_hd;
	int		pipe_fd[2];

	if (redir->expanded == true)
	{
		expanded_hd = expand_heredoc(general, redir);
		if (expanded_hd == NULL || ft_create_pipe(general, pipe_fd) != 0)
			return (1);
		write(pipe_fd[1], expanded_hd, ft_strlen(expanded_hd));
		if (dup2_wrapper(general, pipe_fd[0], 0) != 0)
			return (close_fds(pipe_fd), 1);
		close_fds(pipe_fd);
	}
	else
	{
		if (dup2_wrapper(general, redir->pipe_read_end, 0) != 0)
		{
			ft_close(redir->pipe_read_end);
			redir->pipe_read_end = -1;
			return (1);
		}
		ft_close(redir->pipe_read_end);
		redir->pipe_read_end = -1;
	}
	return (0);
}
