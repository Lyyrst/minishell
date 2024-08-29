/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberkrou <bberkrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 14:14:22 by bberkrou          #+#    #+#             */
/*   Updated: 2024/04/05 03:22:09 by bberkrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

typedef enum e_redirection_type {
	T_REDIRECT_NONE,
	T_REDIRECT_IN,
	T_REDIRECT_OUT,
	T_APPEND,
	T_HEREDOC,
	T_HEREDOC_NO_EXPEND
}	t_redirection_type;

typedef struct s_redirection {
	t_redirection_type		type;
	char					*filename;
	struct s_redirection	*next;
}	t_redirection;

typedef struct s_ast_node {
	t_token_type		type;
	t_token				*token;
	t_redirection		*redirections;
	t_redirection		**here_doc;
	struct s_ast_node	*left;
	struct s_ast_node	*right;
	struct s_ast_node	*parent;
}	t_ast_node;

t_ast_node			*build_ast(t_token **tokens, t_redirection **here_doc);
t_ast_node			*create_ast_node(t_token **token, t_redirection **here_doc);

t_token				*copy_token(t_token *src);
void				remove_token_split(t_token *tokens);
int					is_split_token(t_token_type token);

t_redirection_type	ft_type_to_redirection(t_token_type token);
void				ft_redirectionadd_back(t_redirection **redirection_lst, \
												t_redirection *new);
t_redirection		*ft_redirection_new(char *filename, \
												t_redirection_type type);
t_redirection		*get_pars_redirection(t_token **token);
int					setup_redirections(t_redirection *redirections);
void				create_solitude_node(t_ast_node **root, t_token **tokens, \
											t_redirection **here_doc);
#endif
