/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lib_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberkrou <bberkrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 15:51:36 by bberkrou          #+#    #+#             */
/*   Updated: 2024/03/30 15:56:20 by bberkrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_total_lenght(char **strings)
{
	int	i;
	int	total_length;

	i = 0;
	total_length = 0;
	while (strings[i])
		total_length += ft_strlen(strings[i++]);
	return (total_length);
}

int	ft_arraylen(char **strings)
{
	int	i;

	i = 0;
	while (strings[i])
		i++;
	return (i);
}
