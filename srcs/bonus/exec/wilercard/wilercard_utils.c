/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wilercard_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberkrou <bberkrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 16:40:01 by bberkrou          #+#    #+#             */
/*   Updated: 2024/04/02 14:11:50 by bberkrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_args_number(t_token *token)
{
	int	i;

	i = 0;
	while (token)
	{
		i++;
		token = token->next;
	}
	return (i);
}

int	counter_wilercard(char *filtre)
{
	int	i;

	i = 0;
	while (*filtre)
	{
		if (*filtre == '*')
			i++;
		filtre++;
	}
	return (i);
}

int	process_replace_wilercard(t_token **lst)
{
	t_token	*expend_lst;
	t_token	*save_next;
	char	*args_wilercard;
	char	**ag_spl;
	int		i;

	i = 0;
	expend_lst = NULL;
	save_next = (*lst)->next;
	(*lst)->next = NULL;
	args_wilercard = expend_wilercard((*lst)->value);
	if (!args_wilercard)
		return (0);
	ag_spl = ft_split(args_wilercard, ' ');
	if (!ag_spl)
		return (0);
	while (ag_spl[i])
		if (*ag_spl)
			add_token(&expend_lst, new_token(ag_spl[i++], ARGUMENT));
	sort_wilercard(&expend_lst);
	add_token(&expend_lst, save_next);
	add_token(lst, expend_lst);
	ft_free_tab(ag_spl);
	free(args_wilercard);
	return (1);
}

int	replace_wilercard(t_token **token)
{
	t_token	*cursor;

	if (!token || !*token)
		return (0);
	cursor = *token;
	while (cursor)
	{
		if (cursor->type == WILERCARD)
			if (!process_replace_wilercard(&cursor))
				return (0);
		cursor = cursor->next;
	}
	return (1);
}
