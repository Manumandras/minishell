/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_missing_token.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manuelmittelbach <manuelmittelbach@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 12:08:52 by mmittelb          #+#    #+#             */
/*   Updated: 2026/03/24 19:30:42 by manuelmitte      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "libft.h"
#include "parse.h"
#include "exec.h"
#include "utils.h"

static void	child_parse_token(t_general *general, char *trimmed_line, int fd[2])
{
	char		*new_trimmed_line;
	char		*new_line;

	ft_close(fd[0]);
	signal(SIGINT, SIG_DFL);
	new_line = readline("> ");
	if (new_line == NULL)
	{
		write(2, "minishell: syntax error: unexpected end of file\n", 48);
		write(1, "exit\n", 5);
		gc_free_all(general);
		free_env_list(general->env);
		rl_clear_history();
		exit(146);
	}
	add_in_gc(general, new_line);
	signal_check(general);
	new_trimmed_line = gc_strtrim(general, new_line, " \t\n\r\v\f");
	trimmed_line = gc_strjoin(general, trimmed_line, new_trimmed_line);
	write(fd[1], trimmed_line, ft_strlen(trimmed_line));
	ft_close(fd[1]);
	exit_with_status_and_cleanup(general, general->exit_status);
}

static char	*read_line_from_fd(t_general *general, int fd)
{
	char	buf[2];
	int		bytes_read;
	char	*line;

	line = NULL;
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buf, 1);
		if (bytes_read < 0)
			return (NULL);
		if (bytes_read > 0)
		{
			buf[1] = '\0';
			line = gc_strjoin(general, line, buf);
		}
	}
	return (line);
}

static int	fork_and_parse_token(t_general *general, char **trimmed_line)
{
	pid_t	pid;
	int		status;
	int		fd[2];
	char	*line;

	if (ft_create_pipe(general, fd) != 0)
		return (general->exit_status);
	pid = ft_fork(general);
	if (pid < 0)
		return (general->exit_status);
	if (pid == 0)
		child_parse_token(general, *trimmed_line, fd);
	signal(SIGINT, SIG_IGN);
	ft_close(fd[1]);
	waitpid(pid, &status, 0);
	if (handle_child_status(general, status, trimmed_line, fd[0]) == 1)
		return (1);
	line = read_line_from_fd(general, fd[0]);
	if (line == NULL)
		return (ft_close(fd[0]), 1);
	ft_close(fd[0]);
	*trimmed_line = line;
	return (0);
}

int	missing_token(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '"' || line[i] == '\'')
		{
			i = skip_quotes(line, i, line[i]);
			continue ;
		}
		if (line[i] == '|' && line[i + 1] == '\0')
			return (1);
		if (line[i] == '|' && line[i + 1] == '|' && line[i + 2] == '\0')
			return (1);
		if (line[i] == '&' && line[i + 1] == '&' && line[i + 2] == '\0')
			return (1);
		if (line[i] == '&' || line[i] == '|')
		{
			while (line[i] == '&' || line[i] == '|')
				i++;
		}
		else 
			i++;
	}
	return (0);
}

int	handle_missing_token(t_general *general, char **trimmed_line)
{
	int	status;

	status = 0;
	while (missing_token(*trimmed_line) == 1)
	{
		if (fork_and_parse_token(general, trimmed_line) == 1)
		{
			status = 1;
			break ;
		}
	}
	return (status);
}
