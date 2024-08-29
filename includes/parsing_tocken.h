/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tocken.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberkrou <bberkrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 14:26:26 by bberkrou          #+#    #+#             */
/*   Updated: 2024/04/05 03:21:02 by bberkrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_TOCKEN_H
# define PARSING_TOCKEN_H

# include "minishell.h"

int				check_syntax_pipe(t_token_type type, t_token *lst, t_token *t);
int				is_option(char *token);
void			add_token(t_token **token_list, t_token *new_token);
void			get_last_token_type(t_token_type *lrt, \
								t_token_type *type, char *value);
void			append_token(t_token **token_list, t_token *new_token);
t_token			*new_token(char *value, t_token_type type);
t_token			*create_token(char *value, t_token_type type);
t_token_type	get_token_type(char *token, int is_first_token, t_token *t);
t_token_type	determine_token_type(char *token);
#endif
