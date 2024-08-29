/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberkrou <bberkrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 06:04:58 by bberkrou          #+#    #+#             */
/*   Updated: 2024/04/02 12:45:27 by bberkrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_word_bonus(char **val, char ***split_input, int *i)
{
	int		j;
	char	quote;

	j = 0;
	quote = '\0';
	while ((*val)[j] && ((ft_strncmp(&((*val)[j]), "&&", 2) != 0 && \
		ft_strncmp(&((*val)[j]), "||", 2) != 0 \
		&& ft_strncmp(&((*val)[j]), "(", 1) != 0 \
		&& ft_strncmp(&((*val)[j]), ")", 1) != 0) || quote))
	{
		if ((*val)[j] == '\'' || (*val)[j] == '"')
		{
			if (quote == (*val)[j])
				quote = '\0';
			else if (quote == '\0')
				quote = (*val)[j];
		}
		j++;
	}
	if (j > 0)
	{
		(*split_input)[*i] = ft_strndup(*val, j);
		*val += j;
		(*i)++;
	}
}

void	add_or_and_operator(char **input, char ***split_input, int *i)
{
	if (**input == '|')
	{
		if (*(*input + 1) == '|')
		{
			(*split_input)[*i] = ft_strndup(*input, 2);
			*input += 2;
			(*i)++;
		}
	}
	else if (**input == '&')
	{
		if (*(*input + 1) == '&')
		{
			(*split_input)[*i] = ft_strndup(*input, 2);
			*input += 2;
			(*i)++;
		}
	}
}

void	process_add_braquet(char **cursor, int deep_braquet, char quote, \
								int *len_cpy)
{
	while (**cursor && deep_braquet >= 1)
	{
		quote = 0;
		if (**cursor == '\'' || **cursor == '"')
		{
			quote = **cursor;
			(*cursor)++;
			(*len_cpy) += 1;
			while (**cursor && quote != **cursor)
			{
				(*len_cpy) += 1;
				(*cursor)++;
			}
			(*len_cpy) += 1;
			(*cursor)++;
			continue ;
		}
		if (**cursor == '(')
			deep_braquet++;
		else if (**cursor == ')')
			deep_braquet--;
		(*len_cpy) += 1;
		(*cursor)++;
	}
}

void	add_braquet(char **input, char ***split_input, int *i)
{
	int		deep_braquet;
	int		len_cpy;
	char	*cursor;
	char	quote;

	cursor = *input;
	quote = 0;
	if (*cursor == '(')
	{
		cursor++;
		len_cpy = 1;
		deep_braquet = 1;
		process_add_braquet(&cursor, deep_braquet, quote, &len_cpy);
		(*split_input)[*i] = ft_strndup(*input, len_cpy);
		(*split_input)[*i][0] = ' ';
		(*split_input)[*i][ft_strlen((*split_input)[*i]) - 1] = 0;
		*input += len_cpy;
		(*i)++;
	}
}

char	**split_braquet(char *input)
{
	char	**split_input;
	int		i;

	i = 0;
	split_input = malloc(sizeof(char *) * (ft_strlen(input) * 2));
	if (!split_input)
		return (NULL);
	while (*input)
	{
		skip_spaces(&input);
		add_word_bonus(&input, &split_input, &i);
		add_braquet(&input, &split_input, &i);
		add_or_and_operator(&input, &split_input, &i);
		skip_spaces(&input);
	}
	split_input[i] = NULL;
	return (split_input);
}
