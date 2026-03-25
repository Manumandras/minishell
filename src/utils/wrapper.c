/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrapper.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmittelb <mmittelb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 13:35:18 by mmittelb          #+#    #+#             */
/*   Updated: 2025/12/09 13:26:16 by mmittelb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*write3(t_general *general, const char *a,
			const char *b, const char *c)
{
	size_t	len;
	char	*buf;
	size_t	i;
	size_t	j;

	len = ft_strlen(a) + ft_strlen(b) + ft_strlen(c);
	buf = gc_malloc(general, len + 1);
	i = 0;
	j = 0;
	while (a[j])
		buf[i++] = a[j++];
	j = 0;
	while (b[j])
		buf[i++] = b[j++];
	j = 0;
	while (c[j])
		buf[i++] = c[j++];
	buf[i] = '\0';
	write(2, buf, ft_strlen(buf));
	return (buf);
}

int	dup2_wrapper(t_general *general, int fd1, int fd2)
{
	char	*msg;

	if (dup2(fd1, fd2) == -1)
	{
		msg = strerror(errno);
		write3(general, "minishell: dup2: ", msg, "\n");
		general->exit_status = 1;
		return (1);
	}
	return (0);
}

static char	*join3(t_general *general, const char *a,
			const char *b, const char *c)
{
	size_t	len;
	char	*buf;
	size_t	i;
	size_t	j;

	len = ft_strlen(a) + ft_strlen(b) + ft_strlen(c);
	buf = gc_malloc(general, len + 1);
	i = 0;
	j = 0;
	while (a[j])
		buf[i++] = a[j++];
	j = 0;
	while (b[j])
		buf[i++] = b[j++];
	j = 0;
	while (c[j])
		buf[i++] = c[j++];
	buf[i] = '\0';
	return (buf);
}

void	error_with_errno(t_general *general, const char *prefix,
			const char *name)
{
	char	*msg;
	char	*tmp;
	char	*err;

	err = (char *)strerror(errno);
	tmp = join3(general, prefix, name, ": ");
	msg = join3(general, tmp, err, "\n");
	write(2, msg, ft_strlen(msg));
}

int	ft_create_pipe(t_general *general, int pipe_fd[2])
{
	if (pipe(pipe_fd) == -1)
	{
		error_with_errno(general, "minishell: pipe", "");
		general->exit_status = 1;
		return (1);
	}
	return (0);
}
