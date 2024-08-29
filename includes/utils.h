/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberkrou <bberkrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 14:47:11 by bberkrou          #+#    #+#             */
/*   Updated: 2024/03/31 01:56:46 by bberkrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "minishell.h"

void	ft_free_fork(t_ast_node *node, t_env *env);
void	ft_free_redirection_node(t_redirection *redirection);
void	free_tokens(t_token *tokens);
void	ft_free_tab(char **tab);
void	free_token(t_token *tokens);
void	ft_free_ast(t_ast_node *root);
void	ft_free_redirection(t_redirection *redirection);
void	free_env(t_env *env);
void	process_ft_free_ast(t_ast_node *node);

char	*get_type(int type);
int		is_valide_lexer(t_token *tokens, char *command);

int		is_token_redirection(t_token_type token);
int		is_token_file(t_token_type token);

char	*build_prompt(t_env *env);
char	*gnl(int fd);

#endif