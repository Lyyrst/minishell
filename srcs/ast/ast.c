/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberkrou <bberkrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 23:03:25 by bberkrou          #+#    #+#             */
/*   Updated: 2024/04/05 15:20:57 by bberkrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Analyzes tokens to extract redirects.
 *
 * @param token	A pointer to the first token in the list.
 * @return		A pointer to a redirection structure containing 
 * 				extracted redirects.
 */
t_redirection	*get_parse_redirection(t_token *token)
{
	t_redirection		*redirection;
	t_token				*cursor;
	t_redirection_type	type;

	cursor = token;
	redirection = NULL;
	while (cursor)
	{
		if (is_token_redirection(cursor->type))
		{
			type = ft_type_to_redirection(cursor->type);
			if (cursor->next)
			{
				ft_redirectionadd_back(&redirection, \
					ft_redirection_new(ft_strdup(cursor->next->value), type));
			}
		}
		cursor = cursor->next;
	}
	return (redirection);
}

/**
 * Removes redirection and file tokens from a token list.
 *
 * @param tokens A pointer to a pointer to the list of tokens to be cleaned.
 */
void	clear_token_redirection(t_token **tokens)
{
	t_token	*current;
	t_token	*prev;
	t_token	*to_remove;

	prev = NULL;
	current = *tokens;
	while (current)
	{
		if (is_token_redirection(current->type) || is_token_file(current->type))
		{
			to_remove = current;
			if (prev)
				prev->next = current->next;
			else
				*tokens = current->next;
			current = current->next;
			free(to_remove->value);
			free(to_remove);
		}
		else
		{
			prev = current;
			current = current->next;
		}
	}
}

/**
 * Creates a new syntax tree node from a token.
 *
 * @param token		A pointer to a pointer to the token 
 * 					token to be used to create the node.
 * @return 			A pointer to the new syntax tree node
 * 					created, or NULL on failure.
 */
t_ast_node	*create_ast_node(t_token **token, t_redirection **here_doc)
{
	t_ast_node	*node;

	node = malloc(sizeof(t_ast_node));
	if (!node)
		return (NULL);
	if (!token || !*token)
		return (NULL);
	node->type = (*token)->type;
	node->here_doc = here_doc;
	node->redirections = get_parse_redirection(*token);
	clear_token_redirection(token);
	if (token)
		node->token = copy_token(*token);
	else
		node->token = NULL;
	node->left = NULL;
	node->right = NULL;
	node->parent = NULL;
	return (node);
}

/**
 * Creates a syntax tree node for an isolated token.
 *
 * @param root 		A pointer to a pointer to the root node of the tree,
 * 					which will be updated to point to the newly created node.
 * @param tokens 	A pointer to a pointer to the token to be 
 * 					use to create the node.
 */
void	create_solitude_node(t_ast_node **root, t_token **tokens, \
								t_redirection **here_doc)
{
	*root = create_ast_node(tokens, here_doc);
	if (tokens && *tokens)
		free_token(*tokens);
}

/**
 * Builds a syntax tree from a list of tokens.
 *
 * @param tokens	A pointer to a pointer to the first
 * 					token of the token list to be used to build the tree.
 * @return 			A pointer to the root of the constructed syntax tree.
 * 					NULL if the token list is empty or in the event of an error.
 */
t_ast_node	*build_ast(t_token **tokens, t_redirection **here_doc)
{
	t_token		*cursor;
	t_ast_node	*root;
	t_ast_node	*right;

	if (!tokens && !*tokens)
		return (NULL);
	cursor = *tokens;
	root = NULL;
	while (cursor != NULL && !is_split_token(cursor->type))
		cursor = cursor->next;
	if (cursor == NULL)
		create_solitude_node(&root, tokens, here_doc);
	else
	{
		right = build_ast(&cursor->next, here_doc);
		cursor->next = NULL;
		root = create_ast_node(&cursor, here_doc);
		cursor->prev->next = NULL;
		root->left = build_ast(tokens, here_doc);
		root->right = right;
		root->left->parent = root;
		root->right->parent = root;
		free_tokens(cursor);
	}
	return (root);
}
