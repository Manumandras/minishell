/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnieders <jnieders@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 16:57:15 by jnieders          #+#    #+#             */
/*   Updated: 2025/12/08 19:27:13 by jnieders         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"
#include "libft.h"

static int	wildcard_cmp(const char *s1, const char *s2)
{
	size_t			i;
	unsigned char	c1;
	unsigned char	c2;

	i = 0;
	while (s1[i] && s2[i])
	{
		c1 = (unsigned char)s1[i];
		c2 = (unsigned char)s2[i];
		if (ft_tolower(c1) != ft_tolower(c2))
			return (ft_tolower(c1) - ft_tolower(c2));
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

void	sort_match_list(t_match **head)
{
	t_match	*cur;
	char	*tmp;
	int		swapped;

	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		cur = *head;
		while (cur->next)
		{
			if (wildcard_cmp(cur->name, cur->next->name) > 0)
			{
				tmp = cur->name;
				cur->name = cur->next->name;
				cur->next->name = tmp;
				swapped = 1;
			}
			cur = cur->next;
		}
	}
}
