/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntaxe_bonus_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberkrou <bberkrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 15:55:49 by bberkrou          #+#    #+#             */
/*   Updated: 2024/03/29 04:21:03 by bberkrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	skip_quote_revers(const char *input, int *i)
{
	char	quot_type;

	if (*i >= 0 && (input[*i] == '\'' || input[*i] == '"'))
	{
		quot_type = input[(*i)--];
		while (input [*i] && input[*i] != quot_type)
			(*i)--;
	}
}

int	is_operator_revers(char *input, int *i)
{
	if ((*i > 0 && input[*i] == '&' && input[*i - 1] == '&') \
		|| (*i > 0 && input[*i] == '|' && input[*i - 1] == '|'))
	{
		(*i)--;
		return (1);
	}
	return (0);
}

int	check_braquet_operator_revers(char *input)
{
	int		i;

	i = ft_strlen(input);
	while (i >= 0)
	{
		skip_quote_revers(input, &i);
		if (input[i--] == '(')
		{
			while (i >= 0 && (input[i] && input[i] == ' '))
				i--;
			if (i <= 0)
				return (1);
			if (input[i] != '(' && !is_operator_revers(input, &i))
			{
				ft_putstr_fd("bash: syntax error near unexpected token 1`", 2);
				ft_putchar_fd(input[i], 2);
				ft_putstr_fd("'\n", 2);
				g_last_exit_status = 2;
				return (0);
			}
			i--;
		}
	}
	return (1);
}
