/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberkrou <bberkrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 00:00:00 by bberkrou          #+#    #+#             */
/*   Updated: 2024/04/05 14:57:34 by bberkrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	skip_spaces(char **input)
{
	while (**input && is_white_space(**input))
		(*input)++;
}

int	is_meta_char(char c)
{
	return (c == '|' || c == '<' || c == '>' || c == '*');
}

int	is_token_redirection(t_token_type token)
{
	return (token == REDIRECT_IN
		|| token == REDIRECT_OUT
		|| token == REDIRECT_APPEND
		|| token == HERE_DOC);
}

int	is_token_file(t_token_type token)
{
	return (token == INFILE
		|| token == OUTFILE
		|| token == APPENDFILE
		|| token == DELIMITER_NO_EXPEND
		|| token == DELIMITER);
}

int	get_meta_char(char *c)
{
	if (ft_strncmp(c, "|", 1) == 0)
		return (PIPE);
	if (ft_strncmp(c, "<", 1) == 0)
		return (REDIRECT_IN);
	if (ft_strncmp(c, ">", 1) == 0)
		return (REDIRECT_OUT);
	if (ft_strncmp(c, ">>", 2) == 0)
		return (REDIRECT_APPEND);
	if (ft_strncmp(c, "<<", 2) == 0)
		return (HERE_DOC);
	return (0);
}
