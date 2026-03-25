/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_new_argv.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnieders <jnieders@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 19:33:20 by jnieders          #+#    #+#             */
/*   Updated: 2025/12/09 15:06:58 by jnieders         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"
#include "libft.h"

static int	append_matches(t_general *g, char **new_argv, int i, t_match *m)
{
	while (m)
	{
		new_argv[i] = gc_strdup(g, m->name);
		i++;
		m = m->next;
	}
	return (i);
}

char	**c_new_argv(t_general *g, char **old_argv, char *to_repl, t_match *m)
{
	int		i;
	int		size_new_argv;
	int		replaced_once;
	char	**new_argv;

	i = 0;
	replaced_once = 0;
	size_new_argv = count_argv(old_argv) - 1 + count_match_list(m);
	new_argv = gc_malloc(g, sizeof(char *) * (size_new_argv + 1));
	while (*old_argv)
	{
		if (!replaced_once && ft_strcmp(*old_argv, to_repl) == 0)
		{
			i = append_matches(g, new_argv, i, m);
			old_argv++;
			replaced_once = 1;
			continue ;
		}
		new_argv[i++] = gc_strdup(g, *old_argv++);
	}
	new_argv[i] = NULL;
	return (new_argv);
}
