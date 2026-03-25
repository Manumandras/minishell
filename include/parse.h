/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmittelb <mmittelb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 17:57:52 by jnieders          #+#    #+#             */
/*   Updated: 2025/12/10 12:47:39 by mmittelb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "minishell.h"

typedef enum e_redir_type
{
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_HEREDOC
}	t_redir_type;

typedef struct s_redir
{
	t_redir_type		type;

	char				*filename;
	char				*delimiter;
	bool				expanded;
	int					pipe_read_end;
	struct s_redir		*next;
}	t_redir;

typedef enum e_node_type
{
	NODE_COMMAND,
	NODE_PIPE,
	NODE_AND,
	NODE_OR,
	NODE_GROUP,
}	t_node_type;

typedef struct s_ast
{
	t_node_type		type;
	char			**argv;
	t_redir			*redirs;
	struct s_ast	*left;
	struct s_ast	*right;
}	t_ast;

/* ============================= AST ================================== */

int		find_open_bracket(char *line, int pos);
int		find_operator(char *line, char *op1, char *op2, int op_len);
void	free_ast(t_ast *node);
int		ft_error_checks(t_general *general, char *line);
t_ast	*parse_expression(t_general *general, char *line);
int		handle_missing_token(t_general *general, char **trimmed_line);

/* ========================== Redirections ============================== */

char	*remove_redir_from_line(t_general *general, char *line, int pos);
char	*extract_filename(t_general *general, char *line, int pos);
void	redir_add_back(t_redir **lst, t_redir *new);
t_redir	*extract_redirections(t_general *general, char **line);

#endif
