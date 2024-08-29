/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberkrou <bberkrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 08:14:43 by bberkrou          #+#    #+#             */
/*   Updated: 2024/02/21 10:40:25 by bberkrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

void	print_width_string(int width, int *length)
{
	while (width-- > 0)
	{
		ft_putchar_fd(' ', 1);
		(*length)++;
	}
}

void	ft_print_string(va_list args, t_flags flags, int *length)
{
	char	*str;
	int		str_len;
	int		padding;

	str = va_arg(args, char *);
	if (!str)
		if (flags.precision == -1 || flags.precision >= 6)
			str = "(null)";
	str_len = ft_strlen(str);
	if (flags.precision >= 0)
	{
		if (flags.precision < str_len)
			str_len = flags.precision;
	}
	padding = flags.width - str_len;
	if (flags.aligne_left == 0)
		print_width_string(padding, length);
	if (!(flags.precision == 0 && str_len == 0))
	{
		write(1, str, str_len);
		*length += str_len;
	}
	if (flags.aligne_left == 1)
		print_width_string(padding, length);
}

void	ft_print_char(va_list args, t_flags flags, int *length)
{
	char	c;
	int		padding;

	c = (char)va_arg(args, int);
	padding = flags.width - 1;
	if (!flags.aligne_left)
	{
		while (padding-- > 0)
		{
			ft_putchar_fd(' ', 1);
			(*length)++;
		}
	}
	ft_putchar_fd(c, 1);
	(*length)++;
	if (flags.aligne_left)
	{
		while (padding-- > 0)
		{
			ft_putchar_fd(' ', 1);
			(*length)++;
		}
	}
}
