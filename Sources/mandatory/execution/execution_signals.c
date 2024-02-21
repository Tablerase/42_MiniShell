/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_signals.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourgeo <abourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 07:21:25 by abourgeo          #+#    #+#             */
/*   Updated: 2024/02/21 09:29:20 by abourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Includes/minishell.h"

void	sig_handler_interactive(int signum)
{
	if (signum == SIGINT)
	{
		rl_on_new_line();
		write(2, "^C\n", 3);
		rl_replace_line("", 0);
		rl_redisplay();
		g_signal = SIGINT;
	}
}

void	sig_handler_non_interactive(int signum)
{
	if (signum == SIGINT)
	{
		write(2, "\n", 1);
		g_signal = SIGINT;
	}
	if (signum == SIGQUIT)
	{
		write(2, "Quit (core dumped)\n", 19);
		g_signal = SIGQUIT;
	}
}

void	sig_handler_heredoc(int signum)
{
	if (signum == SIGINT)
	{
		write(2, "^C", 2);
		g_signal = SIGINT;
		close(0);
	}
}
