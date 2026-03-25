/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnieders <jnieders@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 18:48:34 by jnieders          #+#    #+#             */
/*   Updated: 2025/12/08 20:04:03 by jnieders         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "env.h"
#include "libft.h"
#include "utils.h"

static void	cd_update_env(t_general *general, char *cwd)
{
	char	*temp;
	int		oldpwd_status;
	int		pwd_status;

	temp = get_env_value(general->env, "PWD");
	if (!temp)
		unset_env(general->env, "OLDPWD");
	else
	{
		oldpwd_status = env_exported_status(general, "OLDPWD");
		pwd_status = env_exported_status(general, "PWD");
		if (oldpwd_status == 0 || (oldpwd_status == -1 && pwd_status == 1))
			set_env(general, "OLDPWD", temp, 0);
		else
			set_env(general, "OLDPWD", temp, 1);
	}
	if (env_exported_status(general, "PWD") == 1)
		set_env(general, "PWD", cwd, 1);
	else
		set_env(general, "PWD", cwd, 0);
}

static int	cd_change_dir(t_general *general, char *new_pwd)
{
	char	*cwd;

	if (chdir(new_pwd) != 0)
	{
		perror("cd");
		return (1);
	}
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (print_getcwd_error());
	add_in_gc(general, cwd);
	cd_update_env(general, cwd);
	return (0);
}

static int	builtin_cd_to_home(t_general *general)
{
	char	*home_path;

	home_path = get_env_value(general->env, "HOME");
	if (!home_path)
	{
		write(2, "minishell: cd: HOME not set\n", 28);
		return (1);
	}
	if (home_path[0] == '\0')
		return (0);
	if (cd_change_dir(general, home_path) == 0)
		return (0);
	return (1);
}

static int	builtin_cd_to_oldpwd(t_general *general)
{
	char	*old_pwd;
	char	*cwd;

	old_pwd = get_env_value(general->env, "OLDPWD");
	if (!old_pwd)
	{
		write(2, "minishell: cd: OLDPWD not set\n", 30);
		return (1);
	}
	if (cd_change_dir(general, old_pwd) == 0)
	{
		cwd = get_env_value(general->env, "PWD");
		if (!cwd)
		{
			perror("cd");
			return (1);
		}
		ft_putstr_fd(cwd, 1);
		write(1, "\n", 1);
		return (0);
	}
	return (1);
}

int	builtin_cd(t_general *general, char **argv)
{
	if (argv[1] && argv[2])
	{
		write(2, "minishell: cd: too many arguments\n", 34);
		return (1);
	}
	if (!argv[1])
		return (builtin_cd_to_home(general));
	if (ft_strcmp(argv[1], "-") == 0)
		return (builtin_cd_to_oldpwd(general));
	if (cd_change_dir(general, argv[1]) == 0)
		return (0);
	return (1);
}
