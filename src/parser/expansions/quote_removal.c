/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_removal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnieders <jnieders@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 13:14:47 by jnieders          #+#    #+#             */
/*   Updated: 2025/12/04 16:43:13 by jnieders         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "expansions.h"

char	*remove_quotes_str(t_general *general, char *old_str)
{
	int		i;
	char	mode;
	char	*clean;

	i = 0;
	mode = 0;
	clean = gc_strdup(general, "");
	while (old_str[i])
	{
		if (update_quote_mode(old_str[i], &mode))
		{
			i++;
			continue ;
		}
		clean = gc_append_char(general, clean, old_str[i]);
		i++;
	}
	return (clean);
}

char	**remove_quotes(t_general *general, char **argv)
{
	int		i;
	int		j;
	char	mode;
	char	*clean;
	char	**new_argv;

	i = 0;
	new_argv = gc_malloc(general, sizeof(char *) * (count_argv(argv) + 1));
	while (argv && argv[i])
	{
		j = 0;
		mode = 0;
		clean = gc_strdup(general, "");
		while (argv[i][j])
		{
			if (!update_quote_mode(argv[i][j], &mode))
				clean = gc_append_char(general, clean, argv[i][j]);
			j++;
		}
		new_argv[i] = clean;
		i++;
	}
	new_argv[i] = NULL;
	return (new_argv);
}
