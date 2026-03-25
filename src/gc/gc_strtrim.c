/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmittelb <mmittelb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 12:35:01 by jnieders          #+#    #+#             */
/*   Updated: 2025/12/09 11:33:26 by mmittelb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

static int	ftj_countup(const char *s1, const char *set)
{
	int	i;
	int	j;

	i = 0;
	while (s1[i])
	{
		j = 0;
		while (set[j])
		{
			if (set[j] == s1[i])
				break ;
			j++;
		}
		if (set[j] != '\0')
			i++;
		else
			break ;
	}
	return (i);
}

static int	ftj_countback(const char *s1, const char *set)
{
	int	i;
	int	j;

	i = ft_strlen(s1) - 1;
	while (i >= 0)
	{
		j = 0;
		while (set[j])
		{
			if (set[j] == s1[i])
				break ;
			j++;
		}
		if (set[j] != '\0')
			i--;
		else
			break ;
	}
	return (i);
}

char	*gc_strtrim(t_general *general, char const *s1, char const *set)
{
	int		size;
	int		start;
	int		end;
	char	*ptr;

	if (!s1 || !set)
		return (NULL);
	start = ftj_countup(s1, set);
	end = ftj_countback(s1, set);
	if (start > end)
		return (gc_strdup(general, ""));
	size = end - start + 1;
	ptr = gc_malloc(general, size + 1);
	ptr = ft_memcpy(ptr, &s1[start], (size_t)size);
	ptr[size] = '\0';
	return (ptr);
}
