/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberkrou <bberkrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 16:08:43 by bberkrou          #+#    #+#             */
/*   Updated: 2024/04/05 15:42:46 by bberkrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Divides the input string into a list of substrings based on spaces
 * and redirection and logical operators, while handling quotation marks.
 *
 * @param input 	The input string to be split.
 * @return 			An array of substrings resulting from 
 * 					the division of the input.
 */
char	**ft_split_input(char *input)
{
	char	**split_input;
	int		i;

	i = 0;
	split_input = ft_calloc(sizeof(char *), (ft_strlen(input) * 2));
	if (!split_input)
		return (NULL);
	while (*input)
	{
		skip_spaces(&input);
		add_word(&input, &split_input, &i);
		add_pipe(&input, &split_input, &i);
		add_redirection_operator(&input, &split_input, &i);
		skip_spaces(&input);
	}
	if (i < (int)ft_strlen(input) * 2)
		split_input[i] = NULL;
	return (split_input);
}

int	check_split_input(char **split_input)
{
	int	i;

	i = 0;
	while (split_input[i])
	{
		if ((ft_strcmp(split_input[i], "|") == 0 && split_input[i + 1] == NULL) \
		|| (ft_strcmp(split_input[i], "|") == 0 && split_input[i - 1] == NULL))
		{
			ft_putstr_fd("bash: syntax error near unexpected", 2);
			ft_putstr_fd(" token `newline'\n", 2);
			g_last_exit_status = 2;
			return (0);
		}
		i++;
	}
	return (1);
}

char	*expend_val(t_token *token, t_env *env)
{
	char	*expend_val;

	if (token && token->prev && (ft_strcmp(token->prev->value, "<<") == 0))
	{
		expend_val = ft_strdup(token->value);
		return (expend_val);
	}
	expend_val = ft_expand_envvar(token->value, env);
	return (expend_val);
}

t_token	*re_split_tokens(t_token *tokens)
{
	t_token	*res;
	t_token	*cursor;
	char	**split_input;
	char	**save;

	cursor = tokens;
	res = NULL;
	while (cursor)
	{
		if (cursor->type == UNKNOWN)
		{
			add_token(&res, new_token(cursor->value, cursor->type));
			cursor = cursor->next;
			continue ;
		}
		split_input = ft_split_input(cursor->value);
		save = split_input;
		while (*split_input)
			add_token(&res, new_token(*split_input++, cursor->type));
		ft_free_tab(save);
		cursor = cursor->next;
	}
	return (res);
}

t_token	*pre_tokens(char **split_input, t_env *env)
{
	t_token	*tokens_lst;
	t_token	*cursor;
	t_token	*res;
	char	*val;

	tokens_lst = NULL;
	while (*split_input)
	{
		add_token(&tokens_lst, new_token(*split_input, UNKNOWN));
		split_input++;
	}
	cursor = tokens_lst;
	while (cursor)
	{
		val = expend_val(cursor, env);
		if (val && ft_strlen(val) != 0)
			cursor->type = KNOWN;
		free(cursor->value);
		cursor->value = val;
		cursor = cursor->next;
	}
	res = re_split_tokens(tokens_lst);
	free_tokens(tokens_lst);
	return (res);
}
