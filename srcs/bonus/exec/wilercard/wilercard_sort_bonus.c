/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wilercard_sort_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberkrou <bberkrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 10:35:12 by bberkrou          #+#    #+#             */
/*   Updated: 2024/04/02 14:41:36 by bberkrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_val(char c)
{
	char	cpt;
	int		i;

	i = 0;
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
	{
		if (c >= 'a' && c <= 'z')
			cpt = 'a';
		else
		{
			cpt = 'A';
			i++;
		}
		while (cpt != c)
		{
			cpt++;
			i += 2;
		}
		return (254 + i);
	}
	else if (c >= '0' && c <= '9')
		return (127 + c);
	else
		return (c);
}

int	is_swap(t_token *token1, t_token *token2)
{
	char	*val;
	char	*val2;

	val = token1->value;
	val2 = token2->value;
	while (*val || *val2)
	{
		if (get_val(*val) > get_val(*val2))
			return (1);
		else if (get_val(*val) == get_val(*val2))
		{
			val++;
			val2++;
		}
		else
			return (0);
	}
	return (0);
}

int	swap_wilercard(t_token **value, t_token **next_value)
{
	char	*tmp;

	if (!value || !next_value)
		return (-1);
	if (is_swap(*value, *next_value))
	{
		tmp = (*value)->value;
		(*value)->value = (*next_value)->value;
		(*next_value)->value = tmp;
		return (1);
	}
	else
		return (0);
}

int	wilercard_is_sort(t_token *token)
{
	t_token	*cursor;

	if (!token)
		return (-1);
	cursor = token;
	while (cursor && cursor->next)
	{
		if (is_swap(cursor, cursor->next))
			return (0);
		cursor = cursor->next;
	}
	return (1);
}

void	sort_wilercard(t_token **token)
{
	t_token	*cursor;

	if (!token || !*token)
		return ;
	cursor = *token;
	while (cursor && cursor->next && !wilercard_is_sort(*token))
	{
		if (swap_wilercard(&cursor, &(cursor->next)))
			cursor = *token;
		else
			cursor = cursor->next;
	}
}
