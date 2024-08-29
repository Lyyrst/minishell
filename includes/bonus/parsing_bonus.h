/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberkrou <bberkrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 19:30:16 by bberkrou          #+#    #+#             */
/*   Updated: 2024/04/05 03:26:13 by bberkrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_BONUS_H
# define PARSING_BONUS_H

# include "../minishell.h"

int		check_braquet_closed(const char *input);
int		check_braquet_operator(char *input);
int		check_braquet_operator_revers(char *input);
int		check_cmd_syntaxe(char *cmd);
int		is_operator(char *input, int *i);
int		print_braquet_error(int braquet_count);
int		check_operator(t_token *tokens);
int		print_error_braquet_close(int braquet_count);
int		get_token_length(char *input);
char	**split_braquet(char *input);
char	**split_braquet(char *input);
void	skip_quote(const char *input, int *i);
t_token	*lexer_bonus(char *command);
t_token	*tokenize_bonus(char **split_input);
void	get_parse_hd_bonus(t_ast_node **node, t_env *env, \
							t_redirection **here_doc);
void	process_get_parse_hd(t_ast_node **node, t_env *env, \
							t_redirection **here_doc);
#endif
