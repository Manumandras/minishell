/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnieders <jnieders@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 15:00:04 by jnieders          #+#    #+#             */
/*   Updated: 2025/12/04 16:10:36 by jnieders         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

char	*gc_append_char(t_general *general, char *str, char c)
{
	char	tmp[2];
	char	*new_str;

	tmp[0] = c;
	tmp[1] = '\0';
	if (!str)
		return (gc_strdup(general, tmp));
	new_str = gc_strjoin(general, str, tmp);
	gc_free_one(general, str);
	return (new_str);
}

char	*gc_append_str(t_general *general, char **str1, char **str2)
{
	char	*new_str;

	new_str = gc_strjoin(general, *str1, *str2);
	gc_free_one(general, *str1);
	gc_free_one(general, *str2);
	return (new_str);
}

char	*gc_strjoin(t_general *general, const char *s1, const char *s2)
{
	char	*ptr;
	size_t	len1;
	size_t	len2;
	size_t	i;
	size_t	j;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	ptr = gc_malloc(general, len1 + len2 + 1);
	i = 0;
	while (i < len1)
	{
		ptr[i] = s1[i];
		i++;
	}
	j = 0;
	while (j < len2)
		ptr[i++] = s2[j++];
	ptr[i] = '\0';
	return (ptr);
}

char	*gc_substr(t_general *general, char const *s, size_t start, size_t len)
{
	size_t		i;
	char		*ptr;

	i = 0;
	if (start >= ft_strlen(s))
	{
		ptr = malloc(1);
		if (!ptr)
			return (NULL);
		ptr[0] = '\0';
		return (ptr);
	}
	if (ft_strlen(&s[start]) < len)
		len = ft_strlen(s) - start;
	ptr = gc_malloc(general, len + 1);
	if (!ptr)
		return (NULL);
	while (i < len)
	{
		ptr[i] = s[start + i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}
