/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_syntax.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmittelb <mmittelb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 14:12:03 by mmittelb          #+#    #+#             */
/*   Updated: 2025/12/08 19:30:42 by mmittelb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error_handling.h"

int	ft_error_checks(t_general *general, char *line)
{
	if (unclosed_quotes(general, line) != 0)
		return (1);
	if (unclosed_brackets(general, line) != 0)
		return (1);
	if (check_op_syntax(general, line) != 0)
		return (1);
	if (check_redir_syntax(general, line) != 0)
		return (1);
	return (0);
}
