/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnieders <jnieders@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 14:56:49 by jnieders          #+#    #+#             */
/*   Updated: 2026/01/13 11:29:39 by jnieders         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "minishell.h"

typedef struct s_env
{
	char			*key;
	char			*value;
	int				exported;
	struct s_env	*next;
}	t_env;

void	set_env(t_general *general, char *key, char *value, int exported);
char	*get_env_value(t_env *head, char *key);
void	free_env_list(t_env *head);
int		env_count_exported_nodes(t_env *head);
char	**env_to_array(t_general *general);
int		env_exported_status(t_general *general, char *key);
int		env_set_exported(t_general *general, char *key);
void	env_handle_append(t_general *general, char *key, char *add, int exp);
void	init_env(t_general *general, char **envp);
t_env	*unset_env(t_env *head, char *key);
t_env	*env_new_node(t_general *general, char *key, char *value, int exported);

#endif
