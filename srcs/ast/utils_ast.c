/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberkrou <bberkrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 23:01:38 by bberkrou          #+#    #+#             */
/*   Updated: 2024/04/05 15:21:19 by bberkrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_split_token(t_token_type token)
{
	return (token == PIPE);
}

/**
 * Copies an existing token.
 *
 * @param src 	A pointer to the token to be copied.
 * @return		A pointer to a new copy of the token.
 */
t_token	*copy_token(t_token *src)
{
	t_token	*dst;

	if (src == NULL)
		return (NULL);
	dst = malloc(sizeof(t_token));
	if (dst == NULL)
		return (NULL);
	dst->type = src->type;
	dst->next = src->next;
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
