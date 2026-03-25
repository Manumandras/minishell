/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmittelb <mmittelb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 13:28:40 by mmittelb          #+#    #+#             */
/*   Updated: 2025/12/11 13:20:14 by mmittelb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "libft.h"
#include "expansions.h"
#include "env.h"
#include "utils.h"
#include <sys/stat.h>

static void	try_exec_direct(char **command, t_general *general,
				char **env_arr)
{
	struct stat	st;

	if (access(command[0], F_OK) != 0)
	{
		write3(general, "minishell: ", \
			command[0], ": No such file or directory\n");
		exit_with_status_and_cleanup(general, 127);
	}
	if (lstat(command[0], &st) == 0)
	{
		if (S_ISDIR(st.st_mode))
		{
			write3(general, "minishell: ", command[0], ": Is a directory\n");
			exit_with_status_and_cleanup(general, 126);
		}
	}
	if (access(command[0], X_OK) == 0)
	{
		execve(command[0], command, env_arr);
		perror(command[0]);
		exit_with_status_and_cleanup(general, 126);
	}
	exit_permission_denied(general, command[0]);
}

static void	try_exec_in_path(char **command, t_general *general,
				char **paths, char **env_arr)
{
	int		i;
	char	*backslash_command;
	char	*path_try;

	i = 0;
	while (paths[i])
	{
		backslash_command = gc_strjoin(general, "/", command[0]);
		path_try = gc_strjoin(general, paths[i], backslash_command);
		if (access(path_try, F_OK) == 0)
		{
			if (access(path_try, X_OK) == 0)
			{
				execve(path_try, command, env_arr);
				error_with_errno(general, "minishell: ", path_try);
				exit_with_status_and_cleanup(general, 127);
			}
			error_with_errno(general, "minishell: ", path_try);
			exit_with_status_and_cleanup(general, 126);
		}
		i++;
	}
}

static void	execute_command(char **command, t_general *general)
{
	char	**env_arr;
	char	*path;
	char	**paths;

	env_arr = env_to_array(general);
	if (ft_strchr(command[0], '/'))
		try_exec_direct(command, general, env_arr);
	path = get_env_value(general->env, "PATH");
	if (!path || path[0] == '\0')
		exit_no_such_file(general, command[0]);
	paths = gc_split(general, path, ':');
	try_exec_in_path(command, general, paths, env_arr);
	exit_command_not_found(general, command[0]);
}

int	execute_bash_cmd(t_general *general, t_redir *redirs, char **argv)
{
	pid_t	pid;
	int		status;
	int		ret;

	pid = ft_fork(general);
	if (pid < 0)
		return (general->exit_status);
	else if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		ret = handle_redirections(general, redirs, 0);
		if (ret != 0 || (argv == NULL || argv[0] == NULL || (*argv)[0] == '\0'))
			exit_with_status_and_cleanup(general, general->exit_status);
		execute_command(argv, general);
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		waitpid(pid, &status, 0);
		set_exitstatus(status, general);
	}
	return (general->exit_status);
}
