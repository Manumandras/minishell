/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmittelb <mmittelb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 16:21:50 by jnieders          #+#    #+#             */
/*   Updated: 2025/12/08 19:37:29 by mmittelb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "exec.h"
#include "libft.h"
#include "utils.h"

void	end_of_line_check(t_general *general, char *line)
{
	if (line == NULL)
	{
		write(1, "exit\n", 5);
		gc_free_all(general);
		free_env_list(general->env);
		exit(general->exit_status);
	}
}

int	skip_quotes(char *line, int i, int c)
{
	i++;
	while (line[i])
	{
		if (line[i] == c)
		{
			i++;
			break ;
		}
		i++;
	}
	return (i);
}

void	free_str_arr(char **str_arr)
{
	int	i;

	if (!str_arr)
		return ;
	i = 0;
	while (str_arr[i])
		free(str_arr[i++]);
	free(str_arr);
	return ;
}

int	count_args(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
		i++;
	return (i);
}

int	print_getcwd_error(void)
{
	char	*msg;

	msg = strerror(errno);
	write(2, "minishell: pwd: error retrieving current directory: ", 53);
	write(2, "getcwd: cannot access parent directories: ", 43);
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
	return (1);
}
