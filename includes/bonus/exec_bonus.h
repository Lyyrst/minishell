/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bonus.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberkrou <bberkrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 19:33:10 by bberkrou          #+#    #+#             */
/*   Updated: 2024/04/05 03:26:25 by bberkrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_BONUS_H
# define EXEC_BONUS_H

# include "../minishell.h"

void	execute_ast_bonus(t_ast_node **node, t_env **env, \
							t_redirection **here_doc);

#endif
