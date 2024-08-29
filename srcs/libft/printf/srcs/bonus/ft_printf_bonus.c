/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberkrou <bberkrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 19:59:42 by bberkrou          #+#    #+#             */
/*   Updated: 2024/02/21 10:40:40 by bberkrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

/*
** Outputs a formatted string according to 'format' and additional arguments.
** Handles conversion specifications.
**
** @param  format    Format string with specifications.
** @return           Total characters written excluding null byte.
*/
int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		lenght;

	if (!format)
		return (-1);
	lenght = 0;
	va_start (args, format);
	ft_pars_format(format, args, &lenght);
	va_end (args);
	return (lenght);
}
