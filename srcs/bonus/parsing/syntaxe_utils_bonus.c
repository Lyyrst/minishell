/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntaxe_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberkrou <bberkrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 12:13:09 by bberkrou          #+#    #+#             */
/*   Updated: 2024/03/28 10:14:48 by bberkrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_operator(char *input, int *i)
{
	if ((input[*i] && input[*i + 1] \
		&& input[*i] == '&' && input[*i + 1] == '&') \
		|| (input[*i] && input[*i + 1] \
		&& input[*i] == '|' && input[*i + 1] == '|'))
	{
		(*i)++;
		return (1);
	}
	return (0);
}

int	print_braquet_error(int braquet_count)
{
	if (braquet_count != 0)
	{
		if (braquet_count > 0)
			ft_putstr_fd("bash: syntax error near unexpected token `)'\n", 2);
		else
			ft_putstr_fd("bash: syntax error near unexpected token `('\n", 2);
		g_last_exit_status = 2;
		return (0);
	}
	return (1);
}

void	skip_quote(const char *input, int *i)
{
	char	quot_type;

	if (input[*i] == '\'' || input[*i] == '"')
	{
		quot_type = input[(*i)++];
		while (input [*i] && input[*i] != quot_type)
			(*i)++;
	}
}

int	print_error_braquet_close(int braquet_count)
{
	if (braquet_count != 0)
	{
		if (braquet_count > 0)
			ft_putstr_fd("bash: syntax error near unexpected token `)'\n", 2);
		else
			ft_putstr_fd("bash: syntax error near unexpected token `('\n", 2);
		g_last_exit_status = 2;
		return (0);
	}
	return (1);
}
