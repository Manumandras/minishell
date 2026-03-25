/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnieders <jnieders@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 18:57:53 by jnieders          #+#    #+#             */
/*   Updated: 2025/12/02 12:54:40 by jnieders         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "libft.h"

static void	env_update_value(t_general *gen, t_env *var, char *value, int exp)
{
	if (var->value)
	{
		free(var->value);
		var->value = NULL;
	}
	if (value)
		var->value = ft_strdup(value);
	else
		var->value = ft_strdup("");
	if (!var->value)
		gc_exit_error(gen, "malloc failed");
	var->exported = exp;
}

static void	env_append(t_general *general, char *key, char *value, int exp)
{
	t_env	*temp;
	t_env	*node;

	node = env_new_node(general, key, value, exp);
	temp = general->env;
	while (temp->next)
		temp = temp->next;
	temp->next = node;
	return ;
}

void	set_env(t_general *general, char *key, char *value, int exported)
{
	t_env	*head;
	t_env	*temp;

	if (!key)
		return ;
	head = general->env;
	if (!head)
	{
		general->env = env_new_node(general, key, value, exported);
		return ;
	}
	temp = head;
	while (temp)
	{
		if (ft_strcmp(temp->key, key) == 0)
		{
			env_update_value(general, temp, value, exported);
			return ;
		}
		temp = temp->next;
	}
	env_append(general, key, value, exported);
}
