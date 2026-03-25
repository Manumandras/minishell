/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnieders <jnieders@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 17:44:19 by jnieders          #+#    #+#             */
/*   Updated: 2026/01/13 12:13:58 by jnieders         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "utils.h"
#include "libft.h"

static int	check_shlvl_value(t_general *general, char *shlvl_value)
{
	int	i;

	i = 0;
	while (shlvl_value[i])
	{
		if (ft_isdigit(shlvl_value[i]))
			i++;
		else
		{
			set_env(general, "SHLVL", "1", 1);
			return (0);
		}
	}
	return (1);
}

static void	handle_shlvl(t_general *general)
{
	int		shlvl_nbr;
	char	*shlvl_value;
	char	*new_shlvl_value;

	shlvl_value = get_env_value(general->env, "SHLVL");
	if (shlvl_value)
	{
		if (check_shlvl_value(general, shlvl_value) == 0)
			return ;
		shlvl_nbr = ft_atoi(shlvl_value);
		shlvl_nbr++;
		new_shlvl_value = ft_itoa(shlvl_nbr);
		set_env(general, "SHLVL", new_shlvl_value, 1);
		free(new_shlvl_value);
	}
	else
		set_env(general, "SHLVL", "1", 1);
}

static char	*join_value(t_general *general, char **env_arg)
{
	char	*value;
	char	*tmp;
	int		i;

	if (!env_arg[1])
		return (NULL);
	value = gc_strdup(general, env_arg[1]);
	i = 2;
	while (env_arg[i])
	{
		tmp = gc_strjoin(general, value, "=");
		value = gc_strjoin(general, tmp, env_arg[i]);
		i++;
	}
	return (value);
}

void	init_env(t_general *general, char **envp)
{
	t_env	*head;
	t_env	*last;
	t_env	*node;
	char	**env_arg;
	int		i;

	head = NULL;
	last = NULL;
	i = 0;
	while (envp[i])
	{
		env_arg = ft_split(envp[i++], '=');
		if (!env_arg)
			gc_exit_error(general, "malloc failed");
		node = env_new_node(NULL, env_arg[0], join_value(general, env_arg), 1);
		free_str_arr(env_arg);
		if (!head)
			head = node;
		else
			last->next = node;
		last = node;
	}
	general->env = head;
	handle_shlvl(general);
	return ;
}
