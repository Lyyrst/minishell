/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tocken.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberkrou <bberkrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 17:45:48 by bberkrou          #+#    #+#             */
/*   Updated: 2024/03/30 16:06:15 by bberkrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_token_length(char *input)
{
	int	length;
	int	in_quotes;

	length = 0;
	in_quotes = 0;
	while (*input && ((*input != ' ') || (*input == ' ' && in_quotes)))
	{
		if (*input == '\"')
			in_quotes = !in_quotes;
		input++;
		length++;
	}
	return (length);
}

int	check_syntax_pipe(t_token_type type, t_token *lst, t_token *tokens)
{
	if (is_token_redirection(type) || type == PIPE)
	{
		ft_putstr_fd("bash: syntax error near unexpected token `", 2);
		ft_putstr_fd(tokens->value, 2);
		ft_putstr_fd("'\n", 2);
		g_last_exit_status = 2;
		free_tokens(lst);
		return (1);
	}
	return (0);
}

void	get_last_token_type(t_token_type *lrt, \
								t_token_type *type, char *value)
{
	if (*lrt == REDIRECT_IN)
		*type = INFILE;
	else if (*lrt == REDIRECT_OUT)
		*type = OUTFILE;
	else if (*lrt == REDIRECT_APPEND)
		*type = APPENDFILE;
	else if (*lrt == HERE_DOC)
	{
		if (ft_strchr(value, '"') != NULL || ft_strchr(value, '\'') != NULL)
			*type = DELIMITER_NO_EXPEND;
		else
			*type = DELIMITER;
	}
	*lrt = CMD;
}

t_token	*tokenize(t_token *tokens)
{
	int				is_first_token;
	t_token_type	last_redirect_type;
	t_token			*token_list;
	t_token_type	type;

	is_first_token = 1;
	last_redirect_type = CMD;
	token_list = NULL;
	while (tokens)
	{
		type = get_token_type(tokens->value, is_first_token, tokens);
		if (is_token_redirection(last_redirect_type))
		{
			if (check_syntax_pipe(type, token_list, tokens))
				return (NULL);
			get_last_token_type(&last_redirect_type, &type, tokens->value);
		}
		else if (is_token_redirection(type))
			last_redirect_type = type;
		add_token(&token_list, new_token(tokens->value, type));
		is_first_token = (type == PIPE);
		tokens = tokens->next;
	}
	return (token_list);
}
