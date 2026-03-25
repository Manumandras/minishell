/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnieders <jnieders@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 12:34:03 by jnieders          #+#    #+#             */
/*   Updated: 2026/01/13 11:59:19 by jnieders         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "utils.h"
#include "libft.h"

void	gc_free_all(t_general *general)
{
	t_gc	*tmp;

	while (general->gc != NULL)
	{
		tmp = general->gc->next;
		free(general->gc->ptr);
		free(general->gc);
		general->gc = tmp;
	}
}

void	gc_free_one(t_general *general, void *ptr)
{
	t_gc	*current_gc;
	t_gc	*prev_gc;

	prev_gc = NULL;
	current_gc = general->gc;
	while (current_gc)
	{
		if (current_gc->ptr == ptr)
		{
			if (prev_gc)
				prev_gc->next = current_gc->next;
			else
				general->gc = current_gc->next;
			free(current_gc->ptr);
			free(current_gc);
			return ;
		}
		prev_gc = current_gc;
		current_gc = current_gc->next;
	}
}

void	gc_exit_error(t_general *general, const char *msg)
{
	if (msg)
		write3(general, "minishell: ", msg, "\n");
	exit_with_status_and_cleanup(general, 1);
}
