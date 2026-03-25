/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manuelmittelbach <manuelmittelbach@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 14:55:47 by jnieders          #+#    #+#             */
/*   Updated: 2026/03/24 19:29:18 by manuelmitte      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/wait.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <dirent.h>
# include <sys/types.h>
# include <stdbool.h>
# include "gc.h"
# include "string.h"

/* ========================= Forward declarations ========================= */

typedef struct s_ast			t_ast;
typedef struct s_env			t_env;
typedef struct s_gc				t_gc;

extern volatile sig_atomic_t	g_received_signal;

typedef struct s_general
{
	int							exit_status;
	int							saved_fd[2];
	int							i;
	t_ast						*ast;
	t_env						*env;
	t_gc						*gc;
}	t_general;

#endif
