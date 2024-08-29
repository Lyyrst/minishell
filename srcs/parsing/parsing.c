/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberkrou <bberkrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 17:40:54 by bberkrou          #+#    #+#             */
/*   Updated: 2024/04/05 15:49:06 by bberkrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Analyzes input string, extends environment variables,
 * divides into substrings, and generates a list of tokens representing
 * command elements.
 *
 * @param input 	The input string containing the command to be analyzed.
 * 
 * @return 			The list of tokens generated from the input string.
 */
t_token	*lexer(char *input, t_env *env)
{
	t_token	*pre_tokens_lst;
	t_token	*token_list;
	char	**split_input;

	token_list = NULL;
	if (!check_quotes_closed(input))
		return (NULL);
	split_input = ft_split_input(input);
	if (!split_input)
		return (NULL);
	if (split_input[0] == 0)
	{
		free(split_input);
		return (NULL);
	}
	pre_tokens_lst = pre_tokens(split_input, env);
	ft_free_tab(split_input);
	token_list = tokenize(pre_tokens_lst);
	free_tokens(pre_tokens_lst);
	clean_quotes_from_tokens(token_list);
	if (!token_list)
		return (NULL);
	return (token_list);
}
