/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_argv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnieders <jnieders@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 13:12:33 by jnieders          #+#    #+#             */
/*   Updated: 2025/12/09 17:35:04 by jnieders         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "expansions.h"

static char	**remove_empty_args(char **argv)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (argv[i])
	{
		if (argv[i][0] != '\0')
		{
			argv[j] = argv[i];
			j++;
		}
		i++;
	}
	argv[j] = NULL;
	return (argv);
}

char	**expand_argv(t_general *general, char **argv)
{
	int	i;
	int	did_expand_flag;

	if (!argv || !*argv)
		return (NULL);
	i = 0;
	while (argv[i])
	{
		did_expand_flag = 1;
		while (did_expand_flag)
		{
			did_expand_flag = 0;
			argv[i] = expand_vars_in_arg(general, argv[i], &did_expand_flag);
		}
		i++;
	}
	remove_empty_args(argv);
	if (!*argv)
		return (NULL);
	argv = wildcards_expansion(general, argv);
	if ((!argv && !argv[0] && argv[0][0] == '"' && argv[0][1] == '"') || 
		(argv[0][0] == '\'' && argv[0][1] == '\''))
		return (argv);
	argv = remove_quotes(general, argv);
	return (argv);
}
