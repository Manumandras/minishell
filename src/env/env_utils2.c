/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnieders <jnieders@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 12:53:41 by jnieders          #+#    #+#             */
/*   Updated: 2025/12/08 16:01:10 by jnieders         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "libft.h"

char	**env_to_array(t_general *general)
{
	char	**env_new;
	char	*temp_str;
	int		count_nodes;
	t_env	*temp;
	int		i;

	count_nodes = env_count_exported_nodes(general->env);
	env_new = gc_malloc(general, sizeof(char *) * (count_nodes + 1));
	i = 0;
	temp = general->env;
	while (temp)
	{
		if (temp->exported == 1)
		{
			temp_str = gc_strjoin(general, temp->key, "=");
			env_new[i] = gc_strjoin(general, temp_str, temp->value);
			i++;
		}
		temp = temp->next;
	}
	env_new[i] = NULL;
	return (env_new);
}

void	free_env_list(t_env *head)
{
	t_env	*temp;

	while (head)
	{
		if (head->key)
			free(head->key);
		if (head->value)
			free(head->value);
		temp = head->next;
		free(head);
		head = temp;
	}
	return ;
}

int	env_set_exported(t_general *general, char *key)
{
	t_env	*temp;

	if (!key)
		return (0);
	temp = general->env;
	while (temp)
	{
		if (ft_strcmp(temp->key, key) == 0)
		{
			temp->exported = 1;
			return (1);
		}
		temp = temp->next;
	}
	return (0);
}
