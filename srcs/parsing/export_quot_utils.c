/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_quot_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberkrou <bberkrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 02:10:02 by bberkrou          #+#    #+#             */
/*   Updated: 2024/04/05 02:20:27 by bberkrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_quote_if_needed(const char **v, int *i, char **res, int *j)
{
	(*res)[(*j)++] = '\"';
	(*res)[(*j)++] = (*v)[(*i)++];
	(*res)[(*j)++] = '\"';
}

void	process_s_quote_if_needed(const char **v, int *i, char **res, int *j)
{
	(*res)[(*j)++] = '\'';
	(*res)[(*j)++] = (*v)[(*i)++];
	(*res)[(*j)++] = '\'';
}
