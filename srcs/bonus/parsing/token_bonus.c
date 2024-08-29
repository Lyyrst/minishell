/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberkrou <bberkrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 05:48:27 by bberkrou          #+#    #+#             */
/*   Updated: 2024/04/04 20:23:33 by bberkrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token_type	get_token_type_bonus(char *token)
{
	if (ft_strncmp(token, "||", 2) == 0)
		return (OR);
	else if (ft_strncmp(token, "&&", 2) == 0)
		return (AND);
	else
		return (UNKNOWN);
}

t_token	*tokenize_bonus(char **split_input)
{
	int				i;
	t_token			*token_list;
	t_token_type	type;

	i = 0;
	token_list = NULL;
	while (split_input[i])
	{
		type = get_token_type_bonus(split_input[i]);
		add_token(&token_list, new_token(split_input[i++], type));
	}
	return (token_list);
}

t_token_type	get_token_type(char *token, int is_first_token, t_token *tokens)
{
	if (tokens->type == UNKNOWN)
		return (UNKNOWN);
	if (ft_strchr(token, '*') != NULL && token[0] != '\'' \
				&& token[0] != '"')
		return (WILERCARD);
	else if (is_first_token && !get_meta_char(token))
		return (CMD);
	else if (is_option(token))
		return (OPTION);
	else if (ft_strcmp(token, "|") == 0)
		return (PIPE);
	else if (ft_strcmp(token, ">") == 0)
		return (REDIRECT_OUT);
	else if (ft_strcmp(token, "<") == 0)
		return (REDIRECT_IN);
	else if (ft_strcmp(token, ">>") == 0)
		return (REDIRECT_APPEND);
	else if (ft_strcmp(token, "<<") == 0)
		return (HERE_DOC);
	else
		return (ARGUMENT);
}
