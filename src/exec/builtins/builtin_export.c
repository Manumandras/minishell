/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmittelb <mmittelb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 13:18:14 by jnieders          #+#    #+#             */
/*   Updated: 2025/12/08 19:52:18 by mmittelb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "env.h"
#include "libft.h"
#include "utils.h"

static int	export_ident_error(t_general *general, const char *arg)
{
	write3(general, "minishell: export: `", arg, "': not a valid identifier\n");
	return (1);
}

int	builtin_export(t_general *general, char **argv)
{
	int				i;
	int				status;
	t_export_arg	exp;

	if (!argv[1])
		return (print_sorted_export_list(general), 0);
	status = 0;
	i = 1;
	while (argv[i])
	{
		identify_exp_mode(general, argv[i], &exp);
		if (exp.mode == EXP_ERROR)
			status = export_ident_error(general, argv[i]);
		if (exp.mode == EXP_PLAIN)
		{
			if (!env_set_exported(general, exp.key))
				set_env(general, exp.key, "", 1);
		}
		else if (exp.mode == EXP_ASSIGN)
			set_env(general, exp.key, exp.value, 1);
		else if (exp.mode == EXP_APPEND)
			env_handle_append(general, exp.key, exp.value, 1);
		i++;
	}
	return (status);
}
