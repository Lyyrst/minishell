/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tocken_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberkrou <bberkrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 17:51:48 by bberkrou          #+#    #+#             */
/*   Updated: 2024/03/30 16:01:23 by bberkrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*ft_token_last(t_token *token)
{
	if (!token)
		return (NULL);
	while (token->next)
		token = token->next;
	return (token);
}

t_token	*new_token(char *value, t_token_type type)
{
	t_token	*new_token;

	new_token = (t_token *)malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->value = ft_strdup(value);
	new_token->type = type;
	new_token->next = NULL;
	new_token->prev = NULL;
	return (new_token);
}

void	add_token(t_token **token_list, t_token *new_token)
{
	t_token	*last;

	if (!token_list || !new_token)
		return ;
	if (!*token_list)
		*token_list = new_token;
	else
	{
		last = ft_token_last(*token_list);
		last->next = new_token;
		new_token->prev = last;
	}
}

int	is_option(char *token)
{
	int	i;

	i = 0;
	if (token && token[0] == '-')
		return (1);
	while (token[i] == '"' || token[i] == '\'')
		i++;
	if (token[i] == '-' && token[i + 1] != '\0')
	{
		if (token[i + 1] == '"' || token[i + 1] == '\'')
		{
			i += 2;
			while (token[i] && (token[i] == '"' || token[i] == '\''))
				i++;
			return (token[i] != '\0');
		}
		return (1);
	}
	return (0);
}

t_token_type	get_token_type(char *token, int is_first_token, t_token *tokens)
{
	if (tokens->type == UNKNOWN)
		return (UNKNOWN);
	if (is_first_token && !get_meta_char(token))
		return (CMD);
	else if (is_option(token))
		return (OPTION);
	else if (strcmp(token, "|") == 0)
		return (PIPE);
	else if (strcmp(token, ">") == 0)
		return (REDIRECT_OUT);
	else if (strcmp(token, "<") == 0)
		return (REDIRECT_IN);
	else if (strcmp(token, ">>") == 0)
		return (REDIRECT_APPEND);
	else if (strcmp(token, "<<") == 0)
		return (HERE_DOC);
	else
		return (ARGUMENT);
}
