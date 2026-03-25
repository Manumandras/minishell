/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_helpers2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmittelb <mmittelb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 13:39:12 by mmittelb          #+#    #+#             */
/*   Updated: 2025/12/10 11:35:04 by mmittelb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "utils.h"

void	reset_fds(t_general *general)
{
	general->saved_fd[0] = -1;
	general->saved_fd[1] = -1;
}

void	exit_no_such_file(t_general *general, char *cmd)
{
	write3(general, "minishell: ", cmd, ": No such file or directory\n");
	exit_with_status_and_cleanup(general, 127);
}

void	exit_permission_denied(t_general *general, char *cmd)
{
	write3(general, "minishell: ", cmd, ": Permission denied\n");
	exit_with_status_and_cleanup(general, 126);
}

void	exit_command_not_found(t_general *general, char *cmd)
{
	write3(general, "", cmd, ": command not found\n");
	exit_with_status_and_cleanup(general, 127);
}
