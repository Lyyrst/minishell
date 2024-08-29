/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntaxe_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbutor-b <kbutor-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 12:09:19 by bberkrou          #+#    #+#             */
/*   Updated: 2024/04/05 17:46:12 by kbutor-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_braquet_closed(const char *input)
{
	int		braquet_count;
	int		i;

	braquet_count = 0;
	i = 0;
	while (input[i])
	{
		skip_quote(input, &i);
		if (input[i] == '(' || input[i] == ')')
		{
			if (input[i] == '(')
				braquet_count++;
			else if (braquet_count == 0)
			{
				braquet_count = -1;
				break ;
			}
			else
				braquet_count--;
		}
		i++;
	}
	return (print_error_braquet_close(braquet_count));
}

int	check_braquet_operator(char *input)
{
	int		i;

	i = 0;
	while (input[i])
	{
		skip_quote(input, &i);
		if (input[i++] == ')')
		{
			while (input[i] && input[i] == ' ')
				i++;
			if (!input[i])
				return (1);
			if (input[i] != ')' && !is_operator(input, &i))
			{
				ft_putstr_fd("bash: syntax error near unexpected token 2`", 2);
				ft_putchar_fd(input[i], 2);
				ft_putstr_fd("'\n", 2);
				g_last_exit_status = 2;
				return (0);
			}
			i++;
		}
	}
	return (1);
}

int	check_operator(t_token *tokens)
{
	int	i;

	i = 0;
	while (tokens)
	{
		if ((i == 0 && is_split_token_bonus(tokens->type))
			|| (is_split_token_bonus(tokens->type) && (tokens->next == NULL \
			|| is_split_token_bonus(tokens->next->type))))
		{
			ft_putstr_fd("bash: syntax error near unexpected token 2`", 2);
			ft_putstr_fd(tokens->value, 2);
			ft_putstr_fd("'\n", 2);
			g_last_exit_status = 2;
			return (0);
		}
		tokens = tokens->next;
		i++;
	}
	return (1);
}

int	check_cmd_syntaxe(char *cmd)
{
	if (!check_quotes_closed(cmd))
		return (0);
	if (!check_braquet_closed(cmd))
		return (0);
	if (!check_braquet_operator(cmd))
		return (0);
	if (!check_braquet_operator_revers(cmd))
		return (0);
	return (1);
}
