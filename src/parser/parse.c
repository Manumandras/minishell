/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmittelb <mmittelb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 14:10:48 by jnieders          #+#    #+#             */
/*   Updated: 2025/12/09 18:28:13 by mmittelb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "libft.h"
#include "utils.h"

static t_ast	*ft_brackets(t_general *general, char **line)
{
	char	*new_line;
	t_ast	*node;
	int		line_length;

	*line = gc_strtrim(general, *line, " \t\n\r\v\f");
	line_length = ft_strlen(*line);
	if (find_open_bracket(*line, line_length - 1) == 0 && \
	(*line)[line_length - 1] == ')')
	{
		new_line = gc_substr(general, *line, 1, line_length - 2);
		node = gc_malloc(general, sizeof(t_ast));
		node->type = NODE_GROUP;
		node->left = parse_expression(general, new_line);
		node->right = NULL;
		node->argv = NULL;
		node->redirs = NULL;
		return (node);
	}
	return (NULL);
}

static t_ast	*create_cmd_node(t_general *general, char *line)
{
	t_ast	*node;

	node = gc_malloc(general, sizeof(t_ast));
	node->type = NODE_COMMAND;
	node->redirs = extract_redirections(general, &line);
	node->left = NULL;
	node->right = NULL;
	line = gc_strtrim(general, line, " ");
	node->argv = skip_quotes_and_split(general, line, ' ');
	return (node);
}

static t_ast	*parse_substring(t_general *general, char *line, \
	int start, int len)
{
	char	*substr;
	t_ast	*node;

	substr = gc_substr(general, line, start, len);
	node = parse_expression(general, substr);
	return (node);
}

static t_ast	*ft_create_op_node(t_general *general, char *line, \
	char *op1, char *op2)
{
	t_ast	*node;
	int		op_pos;
	int		op_len;

	op_len = 2;
	if (op2 == NULL)
		op_len = 1;
	op_pos = find_operator(line, op1, op2, op_len);
	if (op_pos != -1)
	{
		node = gc_malloc(general, sizeof(t_ast));
		if (ft_strncmp(&line[op_pos], "&&", 2) == 0)
			node->type = NODE_AND;
		else if (ft_strncmp(&line[op_pos], "||", 2) == 0)
			node->type = NODE_OR;
		else if (ft_strncmp(&line[op_pos], "|", 1) == 0)
			node->type = NODE_PIPE;
		node->argv = NULL;
		node->redirs = NULL;
		node->left = parse_substring(general, line, 0, op_pos);
		node->right = parse_substring(general, line, op_pos + op_len, \
			ft_strlen(line) - (op_pos + op_len));
		return (node);
	}
	return (NULL);
}

t_ast	*parse_expression(t_general *general, char *line)
{
	t_ast	*node;

	if (!line || *line == '\0')
		return (NULL);
	node = ft_brackets(general, &line);
	if (node != NULL)
		return (node);
	node = ft_create_op_node(general, line, "||", "&&");
	if (node != NULL)
		return (node);
	node = ft_create_op_node(general, line, "|", NULL);
	if (node != NULL)
		return (node);
	return (create_cmd_node(general, line));
}
