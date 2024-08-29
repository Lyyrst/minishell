/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_print_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberkrou <bberkrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 00:45:49 by bberkrou          #+#    #+#             */
/*   Updated: 2024/02/21 10:41:03 by bberkrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

void	print_width(int width, int *length)
{
	while (width-- > 0)
		*length += write(1, " ", 1);
}

void	print_zero(int width, int *length)
{
	while (width-- > 0)
		*length += write(1, "0", 1);
}

void	print_padding(int number, int width, int *length, t_flags flags)
{
	if (flags.space_plus == 1 && number > 0)
	{
		print_width(width - 1, length);
		return ;
	}
	print_width(width, length);
}

int	print_sign(int number, int *length, t_flags flags)
{
	(void) number;
	if (flags.space_plus == 1)
	{
		*length += write(1, "+", 1);
		return (1);
	}
	else if (flags.space_plus == -1)
	{
		*length += write(1, " ", 1);
		return (1);
	}
	else if (flags.space_plus == 3)
	{
		*length += write(1, "-", 1);
		return (1);
	}
	return (0);
}
