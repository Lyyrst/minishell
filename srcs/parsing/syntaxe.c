/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntaxe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberkrou <bberkrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 23:43:24 by bberkrou          #+#    #+#             */
/*   Updated: 2024/04/05 15:42:24 by bberkrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_syntax_error(const char *message, const char *value)
{
	if (value)
	{
		ft_putstr_fd("bash: syntax error near unexpected token `", 2);
		ft_putstr_fd((char *)value, 2);
		ft_putstr_fd("'\n", 2);
	}
	else
	{
		ft_putstr_fd((char *)message, 2);
		ft_putstr_fd("\n", 2);
	}
	g_last_exit_status = 2;
}

int	pross_syntaxer(t_token *c)
{
	if (is_token_redirection(c->type)
		&& (!c->next || is_token_redirection(c->next->type)
			|| c->next->type == PIPE))
	{
		ft_putstr_fd("bash: syntax error near unexpected token", 2);
		if (c->next)
			set_syntax_error("", c->next->value);
		else
			ft_putstr_fd("`newline'\n", 2);
		g_last_exit_status = 2;
		return (0);
	}
	if (c->type == PIPE
		&& (!c->next || c->next->type == PIPE))
	{
		if (c->next)
			set_syntax_error("syntax error near unexpected token", "|");
		else
			set_syntax_error("syntax error near unexpected token", "newline");
		g_last_exit_status = 2;
		return (0);
	}
	return (1);
}

int	check_ambiguous_redirection(t_token *tokens)
{
	if (is_token_file(tokens->type) && ft_strcmp(tokens->value, "*") == 0)
	{
		if (tokens->type == DELIMITER)
		{
			g_last_exit_status = 0;
			return (0);
		}
		ft_putstr_fd("bash: *: ambiguous redirect\n", 2);
		g_last_exit_status = 1;
		return (1);
	}
	return (0);
}

/**
 * Checks token syntax and reports any errors.
 *
 * @param tokens 	A pointer to the first token in the list.
 * @return 			1 if syntax is correct, 0 otherwise.
 */
int	syntaxer(t_token *tokens)
{
	t_token	*c;

	c = tokens;
	if (!c)
		set_syntax_error("syntax error near unexpected token \
			`newline'", NULL);
	else if (c->type == PIPE)
		set_syntax_error("syntax error near unexpected token", "|");
	if (!c || c->type == PIPE)
		return (0);
	while (c)
	{
		if (!pross_syntaxer(c))
			return (0);
		if (check_ambiguous_redirection(c))
			return (0);
		c = c->next;
	}
	return (1);
}
