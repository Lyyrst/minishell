/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hexa_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberkrou <bberkrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 07:49:30 by bberkrou          #+#    #+#             */
/*   Updated: 2024/02/21 10:40:18 by bberkrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

char	*prepare_base(t_flags flags)
{
	if (flags.param == 'x')
		return ("0123456789abcdef");
	else
		return ("0123456789ABCDEF");
}

void	adjust_length_and_width(t_flags *flags, \
									unsigned int number, int *str_len)
{
	if (flags->square == 1)
		flags->width -= 2;
	if (flags->precision == 0 && number == 0)
		(*str_len)--;
	if (flags->precision > *str_len)
		flags->width -= (flags->precision - *str_len);
}

static void	print_hex_prefix(t_flags flags, unsigned int number, int *length)
{
	if (flags.square && number != 0)
	{
		if (flags.param == 'x')
			ft_putstr_fd("0x", 1);
		else
			ft_putstr_fd("0X", 1);
		*length += 2;
	}
}

void	manage_hex_display(t_flags flags, int *length, int str_len, \
							unsigned int number)
{
	if (flags.zero == 1 && flags.precision == -1)
	{
		print_hex_prefix(flags, number, length);
		print_zero(flags.width - str_len, length);
	}
	else if (flags.aligne_left != 1)
	{
		print_padding(number, flags.width - str_len, length, flags);
	}
	if (flags.precision != -1)
	{
		print_hex_prefix(flags, number, length);
		if (str_len < flags.precision)
			print_zero(flags.precision - str_len, length);
	}
	else if (flags.zero == 0)
	{
		print_hex_prefix(flags, number, length);
	}
}

void	ft_print_hexa(va_list args, t_flags flags, int *length)
{
	unsigned int	number;
	char			*base;
	char			*str;
	int				str_len;

	number = va_arg(args, unsigned int);
	base = prepare_base(flags);
	str = ft_uitoa_base(number, base);
	str_len = ft_strlen(str);
	adjust_length_and_width(&flags, number, &str_len);
	manage_hex_display(flags, length, str_len, number);
	if (flags.precision != 0 || number != 0)
		ft_putstr_fd(str, 1);
	if (flags.aligne_left == 1)
		print_padding(number, flags.width - str_len, length, flags);
	*length += str_len;
	free(str);
}
