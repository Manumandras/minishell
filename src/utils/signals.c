/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmittelb <mmittelb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 12:20:43 by mmittelb          #+#    #+#             */
/*   Updated: 2025/12/10 20:33:52 by mmittelb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

volatile sig_atomic_t	g_received_signal = 0;

void	signal_check(t_general *general)
{
	if (g_received_signal == 1)
	{
		general->exit_status = 130;
		g_received_signal = 0;
	}
}

void	handler(int signum)
{
	if (signum == SIGINT)
	{
		g_received_signal = 1;
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	setup_signals(void)
{
	signal(SIGINT, handler);
	signal(SIGQUIT, SIG_IGN);
}
