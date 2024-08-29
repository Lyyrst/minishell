/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberkrou <bberkrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 06:13:07 by bberkrou          #+#    #+#             */
/*   Updated: 2024/04/02 11:58:43 by bberkrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Check the syntax of the abstract syntax tree (AST).
 *
 * @param root A pointer to the root of the AST.
 * @param valide A pointer to a variable indicating the validity of the syntax.
 */
void	check_ast_syntaxe(t_ast_node *root, int *valide)
{
	if (!root || *valide == 0)
		return ;
	else if (root->token->type == KNOWN)
	{
		if (ft_strcmp(root->token->value, " ") == 0)
		{
			*valide = 0;
			return ;
		}
		if (ft_strchr(root->token->value, '&') \
			&& !ft_strnstr(root->token->value, "&&", \
							ft_strlen(root->token->value)))
		{
			*valide = 0;
			return ;
		}
	}
	check_ast_syntaxe(root->left, valide);
	check_ast_syntaxe(root->right, valide);
}

void	check_ast_syntaxe_mandatory(t_ast_node *root, int *valide, t_env *env)
{
	t_token	*tokens;

	(void)env;
	(void)tokens;
	if (!root || *valide == 0)
		return ;
	if (root->token->type == KNOWN)
	{
		tokens = lexer(root->token->value, env);
		if (!is_valide_lexer(tokens, NULL))
		{
			*valide = 0;
			return ;
		}
		free_tokens(tokens);
	}
	check_ast_syntaxe_mandatory(root->left, valide, env);
	check_ast_syntaxe_mandatory(root->right, valide, env);
}

static void	process_build_ast_bonus(t_ast_node **root, t_token **cursor)
{
	t_ast_node	*right;

	(*cursor)->next->prev = NULL;
	right = build_ast_bonus(&(*cursor)->next);
	(*cursor)->next = NULL;
	(*root) = create_ast_node_bonus(cursor);
	(*cursor)->prev->next = NULL;
	(*root)->left = build_ast_bonus(&(*cursor)->prev);
	(*root)->right = right;
	(*root)->left->parent = (*root);
	(*root)->right->parent = (*root);
	free_tokens(*cursor);
}

/**
 * Build the abstract syntax tree (AST) from tokens, 
 * 	with additional features.
 *
 * @param tokens	A pointer to the pointer to the first token.
 * @return			A pointer to the root of the AST, or NULL 
 * 					if tokens are empty.
 */
t_ast_node	*build_ast_bonus(t_token **tokens)
{
	t_token		*cursor;
	t_ast_node	*root;

	if (!tokens && !*tokens)
		return (NULL);
	cursor = ft_token_last(*tokens);
	root = NULL;
	while (cursor != NULL && !is_split_token_bonus(cursor->type))
		cursor = cursor->prev;
	if (cursor == NULL)
		create_solitude_node_bonus(&root, tokens);
	else
		process_build_ast_bonus(&root, &cursor);
	return (root);
}

/**
 * Expand the AST nodes if tokens in ().
 *
 * @param node The current node of the AST.
 * @param env The environment variables.
 */
void	expend_ast(t_ast_node **node, t_env *env, int *i)
{
	if (!node || !(*node))
		return ;
	if ((*node)->token->type == UNKNOWN)
	{
		if (find_operator_tokens((*node)->token))
		{
			if (process_expend_ast(node, i))
				return ;
		}
		else
		{
			(*node)->type = KNOWN;
			(*node)->token->type = KNOWN;
		}
	}
	expend_ast(&((*node)->left), env, i);
	expend_ast(&((*node)->right), env, i);
}
