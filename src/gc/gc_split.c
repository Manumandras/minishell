/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnieders <jnieders@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 12:36:57 by jnieders          #+#    #+#             */
/*   Updated: 2025/12/02 14:29:21 by jnieders         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

static char	**gc_empty_split(t_general *general)
{
	char	**arr;

	arr = gc_malloc(general, sizeof(char *) * 1);
	arr[0] = NULL;
	return (arr);
}

char	**gc_split(t_general *general, char const *s, char c)
{
	char	**arr;
	int		i;

	if (!s)
		return (gc_empty_split(general));
	if (ft_count_words(s, c) == 0)
		return (gc_empty_split(general));
	arr = ft_split(s, c);
	if (!arr)
		gc_exit_error(general, "malloc failed");
	i = 0;
	while (arr[i])
	{
		add_in_gc(general, arr[i]);
		i++;
	}
	add_in_gc(general, arr);
	return (arr);
}
