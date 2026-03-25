/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmittelb <mmittelb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 14:55:45 by jnieders          #+#    #+#             */
/*   Updated: 2025/12/08 18:55:25 by mmittelb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "libft.h"
#include "parse.h"

static int	is_shell_var_command(t_general *general, char **argv)
{
	int				i;
	t_export_arg	exp;

	i = 0;
	while (argv[i])
	{
		identify_exp_mode(general, argv[i], &exp);
		if (exp.mode == EXP_ERROR || exp.mode == EXP_PLAIN)
			return (0);
		i++;
	}
	return (1);
}

static int	is_redir_builtin(const char *cmd)
{
	if (ft_strcmp(cmd, "echo") == 0
		|| ft_strcmp(cmd, "cd") == 0
		|| ft_strcmp(cmd, "pwd") == 0
		|| ft_strcmp(cmd, "export") == 0
		|| ft_strcmp(cmd, "unset") == 0
		|| ft_strcmp(cmd, "env") == 0
		|| ft_strcmp(cmd, "exit") == 0)
		return (1);
	return (0);
}

static int	run_builtins(t_general *general, char **argv)
{
	if (ft_strcmp(argv[0], "echo") == 0)
		return (builtin_echo(argv));
	if (ft_strcmp(argv[0], "cd") == 0)
		return (builtin_cd(general, argv));
	if (ft_strcmp(argv[0], "pwd") == 0)
		return (builtin_pwd());
	if (ft_strcmp(argv[0], "export") == 0)
		return (builtin_export(general, argv));
	if (ft_strcmp(argv[0], "unset") == 0)
		return (builtin_unset(general, argv));
	if (ft_strcmp(argv[0], "env") == 0)
		return (builtin_env(general, argv));
	if (ft_strcmp(argv[0], "exit") == 0)
	{
		if (builtin_exit(general, argv))
			return (general->exit_status);
	}
	return (-1);
}

int	exec_builtins(t_general *general, char **argv, t_redir *redirs, int pid_f)
{
	int	flag;

	if (!argv || !argv[0])
		return (-1);
	if (is_shell_var_command(general, argv))
	{
		flag = handle_redirections(general, redirs, pid_f);
		if (flag != 0)
			return (-2);
		return (builtin_shell_vars(general, argv));
	}
	if (is_redir_builtin(argv[0]))
	{
		flag = handle_redirections(general, redirs, pid_f);
		if (flag != 0)
			return (-2);
	}
	return (run_builtins(general, argv));
}
