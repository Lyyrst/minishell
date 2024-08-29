/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_tokens_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberkrou <bberkrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 16:09:50 by bberkrou          #+#    #+#             */
/*   Updated: 2024/04/05 15:54:27 by bberkrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Adds a word to the list of split strings, handling quotation marks to
 * consider sequences enclosed in quotation marks as a single word.
 *
 * @param input 		Pointer to the input string currently being analyzed.
 * @param split_input 	Address of the list of split strings to 
 * 						to which to add the word.
 * @param i 			Index into the list of strings where to 
 * 						add the new word.
 */
void	add_word(char **input, char ***split_input, int *i)
{
	int		j;
	char	quote;

	j = 0;
	quote = '\0';
	while ((*input)[j] && (((*input)[j] != ' ' && (*input)[j] != '<' && \
			(*input)[j] != '>' && (*input)[j] != '|') || quote))
	{
		if ((*input)[j] == '\'' || (*input)[j] == '"')
		{
			if (quote == (*input)[j])
				quote = '\0';
			else if (quote == '\0')
				quote = (*input)[j];
		}
		j++;
	}
	if (j > 0)
	{
		(*split_input)[*i] = ft_strndup(*input, j);
		*input += j;
		(*i)++;
	}
}

/**
 * Adds a redirection operator to the list of split strings, managing
 * single and double operators such as "<", ">", ">>", and "<<".
 *
 * @param input 		Pointer to the input string currently being analyzed.
 * @param split_input 	Address of the list of split strings to which to * 
 * 						add the operator. the operator.
 * @param i 			Index into the list of strings to which to add the
 * 						the new operator.
 */
void	add_redirection_operator(char **input, char ***split_input, int *i)
{
	if (**input == '<' || **input == '>')
	{
		if ((*(*input + 1) == '<' && **input == '<')
			|| (*(*input + 1) == '>' && **input == '>'))
		{
			(*split_input)[*i] = ft_strndup(*input, 2);
			*input += 2;
		}
		else
		{
			(*split_input)[*i] = ft_strndup(*input, 1);
			*input += 1;
		}
		(*i)++;
	}
}

/**
 * Adds a pipe or logical AND operator to the list of strings 
 * split, handling single and double operators such as "|", "||", and "&&".
 *
 * @param input 		Pointer to the input string currently being analyzed.
 * @param split_input 	Address of the list of split strings to 
 * 						to which to add the operator.
 * @param i 			Index into the list of strings to which to add the new 
 * 						the new operator.
 */
void	add_pipe(char **input, char ***split_input, int *i)
{
	if (**input == '|')
	{
		(*split_input)[*i] = ft_strndup(*input, 1);
		*input += 1;
		(*i)++;
	}
}
