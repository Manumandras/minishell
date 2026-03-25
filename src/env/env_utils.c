/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnieders <jnieders@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 18:04:25 by jnieders          #+#    #+#             */
/*   Updated: 2025/12/02 12:54:11 by jnieders         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "libft.h"

int	env_exported_status(t_general *general, char *key)
{
	t_env	*temp;

	temp = general->env;
	while (temp)
	{
		if (ft_strcmp(temp->key, key) == 0)
			return (temp->exported);
		temp = temp->next;
	}
	return (-1);
}

char	*get_env_value(t_env *head, char *key)
{
	t_env	*temp;

	temp = head;
	while (temp)
	{
		if (ft_strcmp(temp->key, key) == 0)
			return (temp->value);
		temp = temp->next;
	}
	return (NULL);
}

int	env_count_exported_nodes(t_env *head)
{
	int	count_nodes;

	count_nodes = 0;
	while (head)
	{
		if (head->exported == 1)
			count_nodes++;
		head = head->next;
	}
	return (count_nodes);
}

t_env	*env_new_node(t_general *general, char *key,
				char *value, int exported)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		gc_exit_error(general, "malloc failed");
	node->key = ft_strdup(key);
	if (!node->key)
	{
		free(node);
		gc_exit_error(general, "malloc failed");
	}
	if (value)
		node->value = ft_strdup(value);
	else
		node->value = ft_strdup("");
	if (!node->value)
	{
		free(node->key);
		free(node);
		gc_exit_error(general, "malloc failed");
	}
	node->exported = exported;
	node->next = NULL;
	return (node);
}

void	env_handle_append(t_general *general, char *key, char *add, int exp)
{
	char	*old;
	char	*joined;

	old = get_env_value(general->env, key);
	if (!old)
		set_env(general, key, add, exp);
	else
	{
		joined = gc_strjoin(general, old, add);
		set_env(general, key, joined, exp);
	}
	return ;
}
