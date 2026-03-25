/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identify_exp_mode.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnieders <jnieders@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 16:07:01 by jnieders          #+#    #+#             */
/*   Updated: 2025/12/08 17:16:13 by jnieders         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "libft.h"

static int	is_valid_export_key(char *key)
{
	int	i;

	if (!key || key[0] == '\0')
		return (0);
	if (!(ft_isalpha((unsigned char)key[0]) || key[0] == '_'))
		return (0);
	i = 1;
	while (key[i])
	{
		if (!(ft_isalnum((unsigned char)key[i]) || key[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}

static void	exp_plain(t_general *general, char *arg, t_export_arg *exp)
{
	exp->mode = EXP_PLAIN;
	exp->key = gc_strdup(general, arg);
	exp->value = NULL;
	if (!is_valid_export_key(exp->key))
		exp->mode = EXP_ERROR;
}

static void	exp_append(t_general *gen, char *arg, char *e_s, t_export_arg *exp)
{
	exp->mode = EXP_APPEND;
	exp->key = ft_substr(arg, 0, (e_s - arg) - 1);
	add_in_gc(gen, exp->key);
	exp->value = e_s + 1;
	if (!is_valid_export_key(exp->key))
		exp->mode = EXP_ERROR;
}

static void	exp_assign(t_general *gen, char *arg, char *e_s, t_export_arg *exp)
{
	exp->mode = EXP_ASSIGN;
	exp->key = ft_substr(arg, 0, (e_s - arg));
	add_in_gc(gen, exp->key);
	exp->value = e_s + 1;
	if (!is_valid_export_key(exp->key))
		exp->mode = EXP_ERROR;
}

void	identify_exp_mode(t_general *general, char *arg, t_export_arg *exp)
{
	char	*equal_sign;

	equal_sign = ft_strchr(arg, '=');
	if (!equal_sign)
	{
		exp_plain(general, arg, exp);
		return ;
	}
	if (equal_sign > arg && *(equal_sign - 1) == '+')
	{
		exp_append(general, arg, equal_sign, exp);
		return ;
	}
	exp_assign(general, arg, equal_sign, exp);
}
