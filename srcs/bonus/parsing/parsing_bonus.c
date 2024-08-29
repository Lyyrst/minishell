/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberkrou <bberkrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 16:58:12 by bberkrou          #+#    #+#             */
/*   Updated: 2024/04/04 17:30:12 by bberkrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*lexer_bonus(char *command)
{
	char	**split_input;
	t_token	*token_list;

	token_list = NULL;
	if (!check_cmd_syntaxe(command))
		return (NULL);
	split_input = split_braquet(command);
	if (!split_input)
		return (NULL);
	if (split_input[0] == 0)
	{
		free(split_input);
		return (NULL);
	}
	token_list = tokenize_bonus(split_input);
	ft_free_tab(split_input);
	if (!token_list)
		return (NULL);
	if (!check_operator(token_list))
	{
		free_tokens(token_list);
		return (NULL);
	}
	return (token_list);
}
