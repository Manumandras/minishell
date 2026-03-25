/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmittelb <mmittelb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 17:08:00 by mmittelb          #+#    #+#             */
/*   Updated: 2025/12/08 17:50:49 by mmittelb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "libft.h"
#include "utils.h"

static t_redir	*create_redir(t_general *general, char *line, int pos, int type)
{
	t_redir	*new;

	new = gc_malloc(general, sizeof(t_redir));
	new->next = NULL;
	if (type == REDIR_HEREDOC)
	{
		new->delimiter = extract_filename(general, line, pos);
		new->filename = NULL;
		new->pipe_read_end = -1;
	}
	else
	{
		new->filename = extract_filename(general, line, pos);
		new->delimiter = NULL;
		new->pipe_read_end = -1;
	}
	new->type = type;
	return (new);
}

static char	*create_redir_node(t_general *general, \
	char *new_line, int type, t_redir **head)
{
	t_redir	*new_node;
	char	*old_line;
	int		pos;

	pos = general->i;
	new_node = create_redir(general, new_line, pos, type);
	redir_add_back(head, new_node);
	old_line = new_line;
	new_line = remove_redir_from_line(general, old_line, pos);
	return (new_line);
}

static char	*parse_redir_at(t_general *general,
				char *new_line, int i, t_redir **head)
{
	if (new_line[i] == '>')
	{
		if (new_line[i + 1] == '>')
		{
			general->i = i + 2;
			return (create_redir_node(general, new_line,
					REDIR_APPEND, head));
		}
		general->i = i + 1;
		return (create_redir_node(general, new_line,
				REDIR_OUT, head));
	}
	if (new_line[i] == '<')
	{
		if (new_line[i + 1] == '<')
		{
			general->i = i + 2;
			return (create_redir_node(general, new_line,
					REDIR_HEREDOC, head));
		}
		general->i = i + 1;
		return (create_redir_node(general, new_line,
				REDIR_IN, head));
	}
	return (new_line);
}

t_redir	*extract_redirections(t_general *general, char **line)
{
	int		i;
	t_redir	*head;
	char	*new_line;

	head = NULL;
	new_line = gc_strdup(general, *line);
	i = 0;
	while (new_line[i])
	{
		if (new_line[i] == '"' || new_line[i] == '\'')
			i = skip_quotes(new_line, i, new_line[i]);
		if (new_line[i] == '>' || new_line[i] == '<')
		{
			new_line = parse_redir_at(general, new_line, i, &head);
			i = 0;
		}
		else if (new_line[i])
			i++;
	}
	*line = new_line;
	return (head);
}
