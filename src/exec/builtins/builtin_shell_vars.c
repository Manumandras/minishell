/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_shell_vars.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnieders <jnieders@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 11:41:47 by jnieders          #+#    #+#             */
/*   Updated: 2025/12/08 11:32:16 by jnieders         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "env.h"

int	builtin_shell_vars(t_general *general, char **argv)
{
	int				i;
	int				status;
	t_export_arg	exp;

	status = 0;
	i = 0;
	while (argv[i])
	{
		identify_exp_mode(general, argv[i], &exp);
		if (exp.mode == EXP_ASSIGN)
			set_env(general, exp.key, exp.value, 0);
		else if (exp.mode == EXP_APPEND)
			env_handle_append(general, exp.key, exp.value, 0);
		i++;
	}
	return (status);
}
