/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_match_list.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnieders <jnieders@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 19:27:36 by jnieders          #+#    #+#             */
/*   Updated: 2025/12/08 19:56:58 by jnieders         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"
#include "libft.h"

static void	append_match(t_general *general, t_match **node, const char *name)
{
	t_match	*temp;

	if (!(*node))
	{
		(*node) = gc_malloc(general, sizeof(t_match));
		(*node)->name = gc_strdup(general, name);
		(*node)->next = NULL;
	}
	else
	{
		temp = *node;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = gc_malloc(general, sizeof(t_match));
		temp->next->name = gc_strdup(general, name);
		temp->next->next = NULL;
	}
}

static int	match_last_part(char *filename, char *cursor, char *last_part)
{
	size_t	len_file;
	size_t	len_last_part;
	char	*end;

	len_file = ft_strlen(filename);
	len_last_part = ft_strlen(last_part);
	if (len_last_part > len_file)
		return (1);
	end = filename + (len_file - len_last_part);
	if (end < cursor)
		return (1);
	if (ft_strncmp(end, last_part, len_last_part) != 0)
		return (1);
	return (0);
}

static int	match_asterisk(t_general *general, char *pattern, char *filename)
{
	int		i;
	char	*cursor;
	char	*found;
	char	**split_parts;

	split_parts = gc_split(general, pattern, '*');
	i = 0;
	cursor = filename;
	while (split_parts[i])
	{
		if (split_parts[i][0] != '\0')
		{
			found = ft_strnstr(cursor, split_parts[i], ft_strlen(cursor));
			if (!found || (i == 0 && pattern[0] != '*' && found != cursor))
				return (1);
			if (!split_parts[i + 1] 
				&& pattern[ft_strlen(pattern) - 1] != '*'
				&& match_last_part(filename, cursor, split_parts[i]))
				return (1);
			else
				cursor = found + ft_strlen(split_parts[i]);
		}
		i++;
	}
	return (0);
}

void	match_list(t_general *gen, DIR *dir, char *pattern, t_match **a_match)
{
	struct dirent	*entry;

	entry = readdir(dir);
	while (entry)
	{
		if (entry->d_name[0] == '.' && pattern[0] != '.')
		{
			entry = readdir(dir);
			continue ;
		}
		if (match_asterisk(gen, pattern, entry->d_name) == 0)
			append_match(gen, a_match, entry->d_name);
		entry = readdir(dir);
	}
}
