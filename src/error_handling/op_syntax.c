/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_syntax.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmittelb <mmittelb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 13:50:10 by mmittelb          #+#    #+#             */
/*   Updated: 2025/12/11 15:02:16 by mmittelb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error_handling.h"
#include "utils.h"

static int	check_token_after(char *line, int j, t_general *general)
{
	while (line[j] == ' ' || line[j] == '\t')
		j++;
	if (line[j] == '\0')
		return (0);
	if (line[j] == '&')
	{
		return (print_syntax_error(general, "&&"));
	}
	if (line[j] == '|')
	{
		if (line[j + 1] == '|')
			return (print_syntax_error(general, "||"));
		return (print_syntax_error(general, "|"));
	}
	if (line[j] == ')')
		return (print_syntax_error(general, ")"));
	return (0);
}

static int	check_pipe_at(char *line, int i, t_general *general)
{
	int	j;

	j = i - 1;
	while (j >= 0 && (line[j] == ' ' || line[j] == '\t'))
		j--;
	if (j < 0 || line[j] == '(')
	{
		if (line[i + 1] == '|')
			return (print_syntax_error(general, "||"));
		return (print_syntax_error(general, "|"));
	}
	if (line[i + 1] == '|')
		return (check_token_after(line, i + 2, general));
	j = i + 1;
	while (line[j] == ' ' || line[j] == '\t')
		j++;
	if (line[j] == '|')
		return (print_syntax_error(general, "|"));
	if (line[j] == ')' || line[j] == '&')
		return (print_syntax_error_for_char(general, line, j));
	return (0);
}

static int	check_and_at(char *line, int i, t_general *general)
{
	int	j;

	j = i - 1;
	while (j >= 0 && (line[j] == ' ' || line[j] == '\t'))
		j--;
	if (j < 0 || line[j] == '(')
	{
		if (line[1] && line[1] == '&')
			return (print_syntax_error(general, "&&"));
		return (print_syntax_error(general, "&"));
	}
	j = i + 1;
	if (line[j] != '&')
		return (print_syntax_error(general, "&"));
	return (check_token_after(line, j + 1, general));
}

static int	check_op_sequence(char *line, int *i, t_general *general)
{
	int	ret;

	if (line[*i] == '|')
		ret = check_pipe_at(line, *i, general);
	else
		ret = check_and_at(line, *i, general);
	if (ret != 0)
		return (ret);
	if (line[*i] == line[*i + 1])
		(*i)++;
	return (0);
}

int	check_op_syntax(t_general *general, char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '"' || line[i] == '\'')
		{
			i = skip_quotes(line, i, line[i]);
			continue ;
		}
		if (line[i] == '|' || line[i] == '&')
		{
			if (check_op_sequence(line, &i, general))
				return (1);
		}
		if (line[i])
			i++;
	}
	return (0);
}
