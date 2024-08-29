/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberkrou <bberkrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 17:51:56 by bberkrou          #+#    #+#             */
/*   Updated: 2024/04/02 11:58:28 by bberkrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_split_token_bonus(t_token_type token)
{
	return (token == OR || token == AND);
}

int	find_operator_tokens(t_token *tokens)
{
	t_token	*cursor;

	cursor = tokens;
	while (cursor)
	{
		if (ft_strnstr(cursor->value, "&&", ft_strlen(cursor->value))
			|| ft_strnstr(cursor->value, "||", ft_strlen(cursor->value)))
		{
			return (1);
		}
		cursor = cursor->next;
	}
	return (0);
}

int	process_expend_ast(t_ast_node **node, int *i)
{
	void	*ptr;
	t_token	*token_list;

	ptr = (*node)->parent;
	token_list = lexer_bonus((*node)->token->value);
	if (!token_list)
	{
		*i = 2;
		return (1);
	}
	process_ft_free_ast((*node));
	(*node) = build_ast_bonus(&token_list);
	(*node)->parent = ptr;
	return (0);
}
