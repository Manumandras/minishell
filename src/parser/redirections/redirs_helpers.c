/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnieders <jnieders@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 16:54:09 by mmittelb          #+#    #+#             */
/*   Updated: 2025/12/09 17:30:20 by jnieders         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parse.h"
#include "libft.h"
#include "utils.h"

static int	ft_isspace(char c)
{
	return (c == ' ' || c == '\n' || c == '\r'
		|| c == '\v' || c == '\f' || c == '\t');
}

static char	*skip_spaces(char *str)
{
	while (*str && (*str == ' ' || *str == '\n' || *str == '\r' || *str == '\v'
			|| *str == '\f' || *str == '\t'))
		str++;
	return (str);
}

static char	*advance_past_filename(char *str)
{
	int	i;

	i = 0;
	str = skip_spaces(str);
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
			i = skip_quotes(str, i, str[i]);
		else if (str[i] == '<' || str[i] == '>')
			break ;
		else if (ft_isspace(str[i]) == 1)
			break ;
		else
			i++;
	}
	str = skip_spaces(str + i);
	return (str);
}

char	*remove_redir_from_line(t_general *general, char *line, int pos)
{
	char	*prefix;
	char	*after;
	char	*together;
	char	*trimmed;

	prefix = gc_substr(general, line, 0, pos);
	trimmed = gc_strtrim(general, prefix, "<>");
	after = advance_past_filename(line + pos);
	together = gc_strjoin(general, trimmed, after);
	return (together);
}

char	*extract_filename(t_general *general, char *line, int pos)
{
	char	*start;
	int		len;

	start = skip_spaces(line + pos);
	len = 0;
	while (start[len])
	{
		if (start[len] == '"' || start[len] == '\'')
			len = skip_quotes(start, len, start[len]);
		else if (start[len] == '<' || start[len] == '>')
			break ;
		else if (ft_isspace(start[len]) == 1)
			break ;
		else
			len++;
	}
	return (gc_substr(general, start, 0, len));
}
