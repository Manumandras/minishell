/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_expansion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmittelb <mmittelb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 17:53:33 by jnieders          #+#    #+#             */
/*   Updated: 2025/12/09 16:26:50 by mmittelb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"
#include "env.h"
#include "libft.h"

static char	*extract_varname(t_general *general, char *arg, int *i)
{
	int		start;
	char	*name;

	(*i)++;
	start = *i;
	if (!ft_isalpha(arg[*i]) && arg[*i] != '_')
	{
		(*i)++;
		while (ft_isalnum(arg[*i]) || arg[*i] == '_')
			(*i)++;
		return (gc_strdup(general, ""));
	}
	while (ft_isalnum(arg[*i]) || arg[*i] == '_')
		(*i)++;
	name = ft_substr(arg, start, *i - start);
	add_in_gc(general, name);
	return (name);
}

static char	*expand_var(t_general *general, char *old_str, char *arg, int *i)
{
	char	*name;
	char	*value;
	char	*tmp;

	if (arg[*i + 1] == '?')
	{
		*i += 2;
		tmp = ft_itoa(general->exit_status);
		add_in_gc(general, tmp);
		return (gc_append_str(general, &old_str, &tmp));
	}
	name = extract_varname(general, arg, i);
	if (name[0] == '\0')
		return (old_str);
	value = get_env_value(general->env, name);
	if (!value)
		tmp = gc_strdup(general, "");
	else
		tmp = gc_strdup(general, value);
	return (gc_append_str(general, &old_str, &tmp));
}

static void	init_exp_vars(t_general *general, t_exp_vars *ev)
{
	ev->i = 0;
	ev->mode = 0;
	ev->new_arg = gc_strdup(general, "");
}

char	*expand_vars_in_arg(t_general *general, char *old_arg, int *exp_flag)
{
	t_exp_vars	v;

	init_exp_vars(general, &v);
	while (old_arg && old_arg[v.i])
	{
		if (update_quote_mode(old_arg[v.i], &v.mode))
			v.new_arg = gc_append_char(general, v.new_arg, old_arg[v.i]);
		else if (old_arg[v.i] == '$' && v.mode != '\'')
		{
			if (old_arg[v.i + 1] == '?' || old_arg[v.i + 1] == '_' 
				|| ft_isalpha((unsigned char)old_arg[v.i + 1]))
			{
				v.new_arg = expand_var(general, v.new_arg, old_arg, &v.i);
				*exp_flag = 1;
				continue ;
			}
			else
				v.new_arg = gc_append_char(general, v.new_arg, '$');
		}
		else
			v.new_arg = gc_append_char(general, v.new_arg, old_arg[v.i]);
		v.i++;
	}
	return (v.new_arg);
}
