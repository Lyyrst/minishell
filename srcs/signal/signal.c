/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberkrou <bberkrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 00:23:22 by bberkrou          #+#    #+#             */
/*   Updated: 2024/04/05 15:39:52 by bberkrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_sigint_heredoc(int sign_num)
{
	(void)sign_num;
	rl_on_new_line();
	ft_putchar_fd('\n', 1);
	rl_replace_line("", 0);
	g_last_exit_status = -2147483648;
	close(0);
}

/**
 * Signal manager for the SIGINT signal.
 * This function simply displays a line feed.
 *
 * @param sign_num The number of the signal received.
 */
void	process_sigint(int sign_num)
{
	(void)sign_num;
	g_last_exit_status = 130;
	ft_putchar_fd('\n', 1);
}

/**
 * Signal manager for the SIGQUIT signal.
 * This function displays a message indicating that the process has exited
 * with a coredump and updates the global exit code.
 *
 * @param sign_num The number of the signal received.
 */
void	process_sigquit(int sign_num)
{
	(void)sign_num;
	g_last_exit_status = 131;
}

/**
 * Signal manager for the SIGINT signal.
 * This function resets the command line and displays a
 * message indicating that the process has been interrupted.
 *
 * @param sign_num The number of the signal received.
 */
void	process_sigint_muted(int sign_num)
{
	(void)sign_num;
	rl_on_new_line();
	ft_putchar_fd('\n', 1);
	rl_replace_line("", 0);
	rl_redisplay();
	g_last_exit_status = 130;
}

void	setup_signal(void)
{
	signal(SIGINT, process_sigint_muted);
	signal(SIGQUIT, SIG_IGN);
}
