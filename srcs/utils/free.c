/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberkrou <bberkrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 23:27:41 by bberkrou          #+#    #+#             */
/*   Updated: 2024/04/05 16:28:51 by bberkrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_redirection(t_redirection *redirection)
{
	t_redirection	*tmp;

	if (!redirection)
		return ;
	while (redirection)
	{
		tmp = redirection;
		redirection = redirection->next;
		if (tmp->filename)
			free(tmp->filename);
		free(tmp);
	}
}

void	free_tokens(t_token *tokens)
{
	t_token	*tmp;

	if (!tokens)
		return ;
	while (tokens)
	{
		tmp = tokens;
		tokens = tokens->next;
		if (tmp->value)
			free(tmp->value);
		free(tmp);
	}
}

void	free_env(t_env *env)
{
	t_env	*tmp;

	if (!env)
		return ;
	while (env)
	{
		tmp = env;
		env = env->next;
		if (tmp->key)
			free(tmp->key);
		if (tmp->value)
			free(tmp->value);
		free(tmp);
		tmp = NULL;
	}
}

void	process_ft_free_ast(t_ast_node *node)
{
	if (!node)
		return ;
	if (node->token)
		free_tokens(node->token);
	if (node->redirections)
		ft_free_redirection(node->redirections);
	process_ft_free_ast(node->left);
	process_ft_free_ast(node->right);
	free(node);
}

void	ft_free_ast(t_ast_node *node)
{
	if (!node)
		return ;
	while (node && node->parent)
		node = node->parent;
	process_ft_free_ast(node);
}
