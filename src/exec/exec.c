/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmittelb <mmittelb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 12:08:11 by mmittelb          #+#    #+#             */
/*   Updated: 2025/11/26 16:28:39 by mmittelb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "env.h"
#include "utils.h"

static int	fork_group(t_general *general, t_ast *node)
{
	pid_t	pid;
	int		status;

	pid = ft_fork(general);
	if (pid == 0)
	{
		exec_node(node->left, general, 0);
		exit_with_status_and_cleanup(general, general->exit_status);
	}
	waitpid(pid, &status, 0);
	set_exitstatus(status, general);
	return (general->exit_status);
}

int	exec_node(t_ast *node, t_general *general, int in_child)
{
	if (node->type == NODE_COMMAND)
		return (exec_cmd_unit(node->argv, node->redirs, general, in_child));
	if (node->type == NODE_PIPE)
		return (exec_pipe(node->left, node->right, general));
	if (node->type == NODE_AND)
	{
		if (exec_node(node->left, general, in_child) == 0)
			return (exec_node(node->right, general, in_child));
		return (1);
	}
	if (node->type == NODE_OR)
	{
		if (exec_node(node->left, general, in_child) != 0)
			return (exec_node(node->right, general, in_child));
		return (0);
	}
	if (node->type == NODE_GROUP)
		return (fork_group(general, node));
	return (0);
}

int	exec(t_ast *node, t_general *general)
{
	return (exec_node(node, general, 0));
}
