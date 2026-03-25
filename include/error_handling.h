/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmittelb <mmittelb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 13:42:47 by mmittelb          #+#    #+#             */
/*   Updated: 2025/12/08 19:28:09 by mmittelb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_HANDLING_H
# define ERROR_HANDLING_H

# include "minishell.h"

int	print_syntax_error(t_general *general, const char *token);
int	print_syntax_error_for_char(t_general *general, char *line, int i);
int	check_op_syntax(t_general *general, char *line);
int	check_redir_syntax(t_general *general, char *line);
int	unclosed_brackets(t_general *general, char *line);
int	unclosed_quotes(t_general *general, char *line);

#endif