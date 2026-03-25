/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_expansion.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnieders <jnieders@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 17:56:20 by jnieders          #+#    #+#             */
/*   Updated: 2025/12/08 20:01:03 by jnieders         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"
#include "libft.h"

static char	*create_pattern(t_general *general, char *s)
{
	int		i;
	char	mode;
	char	*pattern;

	i = 0;
	mode = 0;
	pattern = gc_strdup(general, "");
	while (s[i])
	{
		if (update_quote_mode(s[i], &mode))
		{
			i++;
			continue ;
		}
		if (s[i] == '*' && mode != 0)
		{
			i++;
			continue ;
		}
		pattern = gc_append_char(general, pattern, s[i]);
		i++;
	}
	return (pattern);
}

static char	**handle_asterisk(t_general *general, char **argv, 
	char *argv_element, int *m_c)
{
	DIR				*dir;
	t_match			*asterisk_match;
	char			*pattern;
	char			**new_argv;

	pattern = create_pattern(general, argv_element);
	dir = opendir(".");
	if (!dir)
		return (argv);
	asterisk_match = NULL;
	match_list(general, dir, pattern, &asterisk_match);
	closedir(dir);
	if (!asterisk_match)
		return (argv);
	sort_match_list(&asterisk_match);
	*m_c = count_match_list(asterisk_match);
	new_argv = c_new_argv(general, argv, argv_element, asterisk_match);
	return (new_argv);
}

static void	init_wc_vars(int *j, char *mode, int *match_count)
{
	*j = 0;
	*mode = 0;
	*match_count = 0;
}

char	**wildcards_expansion(t_general *general, char **argv)
{
	int		i;
	int		j;
	int		match_count;
	char	mode;

	i = 0;
	while (argv && argv[i])
	{
		init_wc_vars(&j, &mode, &match_count);
		while (argv && argv[i] && argv[i][j])
		{
			if (!update_quote_mode(argv[i][j], &mode) 
				&& argv[i][j] == '*' && mode == 0)
			{
				argv = handle_asterisk(general, argv, argv[i], &match_count);
				break ;
			}
			j++;
		}
		if (match_count)
			i += match_count;
		else
			i++;
	}
	return (argv);
}
