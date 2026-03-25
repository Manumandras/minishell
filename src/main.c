/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manuelmittelbach <manuelmittelbach@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 14:53:22 by mmittelb          #+#    #+#             */
/*   Updated: 2026/03/24 19:33:14 by manuelmitte      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "libft.h"
#include "parse.h"
#include "exec.h"
#include "utils.h"

static void	update_general_data(t_general *general)
{
	general->i = 0;
	general->ast = NULL;
	g_received_signal = 0;
}

static void	initialize_general(t_general *general, char **envp)
{
	general->gc = NULL;
	general->saved_fd[0] = -1;
	general->saved_fd[1] = -1;
	general->exit_status = 0;
	if (!envp || !envp[0])
	{
		write3(general, "minishell: ", "failed to initialize environment", "\n");
		exit (1);
	}
	init_env(general, envp);
}

static void	handle_command(t_general *general, char **trimmed_line)
{
	t_ast	*node;

	if (ft_error_checks(general, *trimmed_line) != 0 || \
	handle_missing_token(general, trimmed_line) == 1)
	{
		add_history(*trimmed_line);
		return ;
	}
	add_history(*trimmed_line);
	if (ft_error_checks(general, *trimmed_line) != 0)
		return ;
	node = parse_expression(general, *trimmed_line);
	general->ast = node;
	if (collect_heredocs(general, node) == 1)
	{
		close_open_fds(general->ast);
		gc_free_all(general);
		return ;
	}
	exec(node, general);
	close_open_fds(general->ast);
	gc_free_all(general);
}

static void	main_loop(t_general *general)
{
	char	*line;
	char	*trimmed_line;

	while (1)
	{
		update_general_data(general);
		setup_signals();
		line = readline("minishell: ");
		end_of_line_check(general, line);
		add_in_gc(general, line);
		signal_check(general);
		trimmed_line = gc_strtrim(general, line, " \t\n\r\v\f");
		if (*trimmed_line == '\0')
		{
			gc_free_all(general);
			continue ;
		}
		handle_command(general, &trimmed_line);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_general	general;

	(void)argc;
	(void)argv;
	initialize_general(&general, envp);
	main_loop(&general);
	rl_clear_history();
	free_env_list(general.env);
	return (general.exit_status);
}
