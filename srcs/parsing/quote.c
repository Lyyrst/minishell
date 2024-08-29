/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberkrou <bberkrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 17:34:28 by bberkrou          #+#    #+#             */
/*   Updated: 2024/04/05 15:44:37 by bberkrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Checks whether quotation marks in a string are closed.
 * 
 * @param input The string to check.
 * @return 		1 if closed correctly, otherwise 0.
 */
int	check_quotes_closed(const char *input)
{
	char	quote_type;
	int		i;

	quote_type = '\0';
	i = 0;
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '"')
		{
			if (quote_type == input[i])
				quote_type = '\0';
			else if (quote_type == '\0')
				quote_type = input[i];
		}
		i++;
	}
	if (quote_type != '\0')
	{
		ft_putstr_fd("Syntaxe error: quote ", 2);
		ft_putchar_fd(quote_type, 2);
		ft_putstr_fd(" not closed.\n", 2);
		g_last_exit_status = 2;
		return (0);
	}
	return (1);
}

/**
 * Adds or ignores quotation marks in a string.
 * 
 * @param c 			The character to process.
 * @param temp_str 		The temporary string to add the character to.
 * @param temp_len 		The current length of temp_str.
 * @param current_quote The type of quotation mark currently open (' or ").
 */
void	handle_char(char c, char *temp_str, int *temp_len, char *current_quote)
{
	if (c == '\'' && (*current_quote == '\0' || *current_quote == '\''))
	{
		if (*current_quote == '\'')
			*current_quote = '\0';
		else
			*current_quote = '\'';
	}
	else if (c == '"' && (*current_quote == '\0' || *current_quote == '"'))
	{
		if (*current_quote == '"')
			*current_quote = '\0';
		else
			*current_quote = '"';
	}
	else
		temp_str[(*temp_len)++] = c;
	temp_str[*temp_len] = '\0';
}

/**
 * Removes quotation marks from a token value.
 * 
 * @param value 	The token value to be cleaned.
 * @return 			The string cleaned of quotes.
 */
char	*clean_quotes_from_token_value(const char *value)
{
	char	*temp_str;
	int		temp_len;
	char	current_quote;
	int		i;
	char	*cleaned_value;

	i = 0;
	temp_len = 0;
	current_quote = '\0';
	temp_str = malloc(sizeof(char) * (ft_strlen(value) + 1));
	if (!temp_str)
		return (NULL);
	while (value[i] != '\0')
		handle_char(value[i++], temp_str, &temp_len, &current_quote);
	temp_str[temp_len] = '\0';
	cleaned_value = malloc(temp_len + 1);
	if (!cleaned_value)
	{
		free(temp_str);
		return (NULL);
	}
	ft_strcpy(cleaned_value, temp_str);
	free(temp_str);
	return (cleaned_value);
}

/**
 * Cleans quotes from all tokens in a list.
 * 
 * @param tokens The list of tokens to clean.
 */
void	clean_quotes_from_tokens(t_token *tokens)
{
	char	*cleaned_value;

	while (tokens)
	{
		cleaned_value = clean_quotes_from_token_value(tokens->value);
		free(tokens->value);
		tokens->value = cleaned_value;
		tokens = tokens->next;
	}
}
