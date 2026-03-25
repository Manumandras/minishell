/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmittelb <mmittelb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 13:06:41 by jnieders          #+#    #+#             */
/*   Updated: 2025/12/10 13:09:29 by mmittelb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSIONS_H
# define EXPANSIONS_H

# include "minishell.h"

typedef struct s_match
{
	char			*name;
	struct s_match	*next;
}	t_match;

typedef struct s_exp_vars
{
	int		i;
	char	mode;
	char	*new_arg;
}	t_exp_vars;

/* =============================== EXPANSION =============================== */

char	**expand_argv(t_general *general, char **argv);

/* ============================ VARIABLE EXPANSION ========================= */

char	*expand_vars_in_arg(t_general *general, char *old_arg, int *exp_flag);

/* ============================ WILDCARD EXPANSION ========================= */

char	**c_new_argv(t_general *g, char **old_argv, char *to_repl, t_match *m);
void	sort_match_list(t_match **head);
void	match_list(t_general *gen, DIR *dir, char *pattern, t_match **a_match);
char	**wildcards_expansion(t_general *general, char **argv);

/* ============================ QUOTE REMOVAL ============================== */

char	**remove_quotes(t_general *general, char **argv);
char	*remove_quotes_str(t_general *general, char *old_str);

/* ============================= HELPERS =================================== */

int		update_quote_mode(char c, char *mode);
int		count_argv(char **argv);
int		count_match_list(t_match *node);

#endif
