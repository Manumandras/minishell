/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmittelb <mmittelb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 16:37:30 by mmittelb          #+#    #+#             */
/*   Updated: 2025/12/08 16:46:47 by mmittelb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GC_H
# define GC_H

# include "minishell.h"

typedef struct s_general	t_general;

typedef struct s_gc
{
	void			*ptr;
	struct s_gc		*next;
}	t_gc;

char	*gc_strdup(t_general *general, const char *s);
void	add_in_gc(t_general *general, void *ptr);
void	gc_free_all(t_general *general);
void	gc_free_one(t_general *general, void *ptr);
void	*gc_malloc(t_general *general, size_t size);
char	**gc_split(t_general *general, char const *s, char c);
void	gc_exit_error(t_general *general, const char *msg);
char	*gc_append_char(t_general *general, char *str, char c);
char	*gc_append_str(t_general *general, char **str1, char **str2);
char	*gc_strjoin(t_general *general, const char *s1, const char *s2);
char	*gc_strtrim(t_general *general, char const *s1, char const *set);
char	*gc_substr(t_general *general, char const *s, size_t start, size_t len);

#endif