/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_lib_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberkrou <bberkrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 11:54:31 by bberkrou          #+#    #+#             */
/*   Updated: 2024/04/02 12:00:18 by bberkrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast_node	*create_ast_node_bonus(t_token **token)
{
	t_ast_node	*node;

	node = malloc(sizeof(t_ast_node));
	if (!node)
		return (NULL);
	node->type = (*token)->type;
	node->redirections = NULL;
	if (token)
		node->token = copy_token_bonus(*token);
	else
		node->token = NULL;
	node->here_doc = NULL;
	node->left = NULL;
	node->right = NULL;
	node->parent = NULL;
	return (node);
}

void	create_solitude_node_bonus(t_ast_node **root, t_token **tokens)
{
	*root = create_ast_node_bonus(tokens);
	if (tokens && *tokens)
		free_token(*tokens);
}

t_token	*copy_token_bonus(t_token *src)
{
	t_token	*dst;

	if (src == NULL)
		return (NULL);
	dst = malloc(sizeof(t_token));
	if (dst == NULL)
		return (NULL);
	dst->type = src->type;
	dst->next = src->next;
	dst->prev = src->prev;
	if (src->value != NULL)
	{
		dst->value = ft_strdup(src->value);
		if (dst->value == NULL)
		{
			free(dst);
			return (NULL);
		}
	}
	else
		dst->value = NULL;
	return (dst);
}
