/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs_helper2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmittelb <mmittelb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 17:32:29 by mmittelb          #+#    #+#             */
/*   Updated: 2025/11/27 13:19:07 by mmittelb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parse.h"
#include "libft.h"

static t_redir	*redir_last(t_redir *lst)
{
	t_redir	*last;

	last = NULL;
	while (lst)
	{
		last = lst;
		lst = lst->next;
	}
	return (last);
}

void	redir_add_back(t_redir **lst, t_redir *new)
{
	t_redir	*last;

	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	last = redir_last(*lst);
	last->next = new;
}
