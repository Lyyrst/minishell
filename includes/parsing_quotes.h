/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_quotes.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberkrou <bberkrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 14:25:43 by bberkrou          #+#    #+#             */
/*   Updated: 2024/03/29 05:21:19 by bberkrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_QUOTES_H
# define PARSING_QUOTES_H

# include "minishell.h"

typedef enum s_token_type {
	CMD,
	OPTION,
	ARGUMENT,
	PIPE,
	REDIRECT_IN,
	REDIRECT_OUT,
	REDIRECT_APPEND,
	HERE_DOC,
	INFILE,
	OUTFILE,
	APPENDFILE,
	DELIMITER,
	DELIMITER_NO_EXPEND,
	WILERCARD,
	AND,
	OR,
	UNKNOWN,
	KNOWN
}	t_token_type;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

void	handle_quotes(const char c, int *in_single_quote);
void	clean_quotes_from_tokens(t_token *tokens);
char	*clean_quotes_from_token_value(const char *value);
int		check_quotes_closed(const char *input);
int		is_option(char *token);

#endif
