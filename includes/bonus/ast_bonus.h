/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_bonus.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberkrou <bberkrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 19:35:44 by bberkrou          #+#    #+#             */
/*   Updated: 2024/04/02 11:57:19 by bberkrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_BONUS_H
# define AST_BONUS_H

# include "../minishell.h"

int			is_split_token_bonus(t_token_type token);
int			is_operator(char *input, int *i);
int			is_split_token_bonus(t_token_type token);
int			find_operator_tokens(t_token *tokens);
int			process_expend_ast(t_ast_node **node, int *i);
void		create_solitude_node_bonus(t_ast_node **root, t_token **tokens);
void		expend_ast(t_ast_node **node, t_env *env, int *i);
void		check_ast_syntaxe(t_ast_node *root, int *valide);
void		check_ast_syntaxe_mandatory(t_ast_node *root, int *valide, \
											t_env *env);
t_token		*ft_token_last(t_token *token);
t_token		*copy_token_bonus(t_token *src);
t_ast_node	*create_ast_node_bonus(t_token **token);
t_ast_node	*build_ast_bonus(t_token **tokens);

#endif
