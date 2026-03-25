/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_alloc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmittelb <mmittelb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 12:32:53 by jnieders          #+#    #+#             */
/*   Updated: 2025/12/10 11:28:03 by mmittelb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "utils.h"

void	add_in_gc(t_general *general, void *ptr)
{
	t_gc	*node;

	if (ptr == NULL)
		return ;
	node = malloc(sizeof(t_gc));
	if (!node)
	{
		close_open_fds(general->ast);
		gc_free_all(general);
		write(2, "minishell: malloc failed\n", 25);
		exit(EXIT_FAILURE);
	}
	node->ptr = ptr;
	node->next = general->gc;
	general->gc = node;
}

void	*gc_malloc(t_general *general, size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	add_in_gc(general, ptr);
	return (ptr);
}

char	*gc_strdup(t_general *general, const char *s)
{
	char	*dup;
	size_t	len;

	len = ft_strlen(s) + 1;
	dup = gc_malloc(general, len);
	ft_memcpy(dup, s, len);
	return (dup);
}
