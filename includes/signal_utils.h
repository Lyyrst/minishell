/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_utils.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberkrou <bberkrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 14:55:28 by bberkrou          #+#    #+#             */
/*   Updated: 2024/03/15 15:34:48 by bberkrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_UTILS_H
# define SIGNAL_UTILS_H

# include "minishell.h"

void	process_sigint_heredoc(int sign_num);
void	process_sigint_muted(int sign_num);
void	process_sigint(int sign_num);
void	process_sigquit_muted(int sign_num);
void	process_sigquit(int sign_num);
void	setup_signal(void);

#endif