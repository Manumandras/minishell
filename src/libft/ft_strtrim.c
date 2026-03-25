/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmittelb <mmittelb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 13:57:28 by jnieders          #+#    #+#             */
/*   Updated: 2025/11/19 12:27:00 by mmittelb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

char	*ft_strtrim(char const *s1, char const *set)
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
		return (ft_strdup(""));
	size = end - start + 1;
	ptr = (char *)malloc(sizeof(char) * (size + 1));
	if (ptr == NULL)
		return (NULL);
	ptr = ft_memcpy(ptr, &s1[start], (size_t)size);
	ptr[size] = '\0';
	return (ptr);
}
