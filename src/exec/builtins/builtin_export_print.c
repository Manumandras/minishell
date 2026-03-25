/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_print.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnieders <jnieders@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 19:35:14 by jnieders          #+#    #+#             */
/*   Updated: 2025/12/08 15:39:55 by jnieders         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "env.h"
#include "libft.h"

static char	*export_line_from_var(t_general *general, t_env *var)
{
	const char	*prefix;
	char		*line;
	size_t		i;
	size_t		j;

	prefix = "declare -x ";
	line = gc_malloc(general, (ft_strlen(prefix) + ft_strlen(var->key) \
	+ 1 + 2 + ft_strlen(var->value) + 1));
	i = 0;
	j = 0;
	while (prefix[j])
		line[i++] = prefix[j++];
	j = 0;
	while (var->key[j])
		line[i++] = var->key[j++];
	line[i++] = '=';
	line[i++] = '\"';
	j = 0;
	while (var->value[j])
		line[i++] = var->value[j++];
	line[i++] = '\"';
	line[i] = '\0';
	return (line);
}

static char	**build_export_lines(t_general *general)
{
	int		n;
	int		i;
	char	**arr;
	t_env	*temp;

	n = env_count_exported_nodes(general->env);
	arr = gc_malloc(general, sizeof(char *) * (n + 1));
	i = 0;
	temp = general->env;
	while (temp)
	{
		if (temp->exported == 1)
			arr[i++] = export_line_from_var(general, temp);
		temp = temp->next;
	}
	arr[i] = NULL;
	return (arr);
}

static void	sort_str_array(char **arr)
{
	int		i;
	int		swapped;
	char	*tmp;

	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		i = 0;
		while (arr[i] && arr[i + 1])
		{
			if (ft_strcmp(arr[i], arr[i + 1]) > 0)
			{
				tmp = arr[i];
				arr[i] = arr[i + 1];
				arr[i + 1] = tmp;
				swapped = 1;
			}
			i++;
		}
	}
}

void	print_sorted_export_list(t_general *general)
{
	int		i;
	char	**lines;

	if (!general->env)
		return ;
	lines = build_export_lines(general);
	sort_str_array(lines);
	i = 0;
	while (lines[i])
	{
		ft_putstr_fd(lines[i], 1);
		write(1, "\n", 1);
		i++;
	}
}
