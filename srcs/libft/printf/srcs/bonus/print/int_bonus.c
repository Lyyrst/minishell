/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberkrou <bberkrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 08:01:19 by bberkrou          #+#    #+#             */
/*   Updated: 2024/02/21 10:40:20 by bberkrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

long int	prepare_number(va_list args, t_flags *flags)
{
	long int	number;

	number = va_arg(args, int);
	if (number < 0)
	{
		flags->space_plus = 3;
		number = -number;
		flags->width--;
	}
	return (number);
}

void	adjust_len_and_width(t_flags *flags, long int number, int *str_len)
{
	if (flags->precision == 0 && number == 0)
		(*str_len)--;
	if (flags->precision > *str_len)
		flags->width -= (flags->precision - *str_len);
}

void	display_int(t_display_info info)
{
	if (info.flags.zero == 1 && info.flags.precision == -1)
	{
		print_sign(info.number, info.length, info.flags);
		print_zero(info.flags.width - info.str_len, info.length);
	}
	else if (info.flags.aligne_left != 1)
		print_padding(info.number, info.flags.width - info.str_len, \
						info.length, info.flags);
	if (info.flags.precision != -1 || info.flags.zero == 0)
	{
		print_sign(info.number, info.length, info.flags);
		if (info.str_len < info.flags.precision)
			print_zero(info.flags.precision - info.str_len, info.length);
	}
	if (info.flags.precision != 0 || info.number != 0)
		ft_putstr_fd(info.str, 1);
	if (info.flags.aligne_left == 1)
		print_padding(info.number, info.flags.width - info.str_len, \
						info.length, info.flags);
}

void	ft_print_int(va_list args, t_flags flags, int *length)
{
	t_display_info	info;
	long int		number;
	char			*str;
	int				str_len;

	number = prepare_number(args, &flags);
	str = ft_ltoa(number);
	str_len = ft_strlen(str);
	adjust_len_and_width(&flags, number, &str_len);
	info.flags = flags;
	info.length = length;
	info.str_len = str_len;
	info.number = number;
	info.str = str;
	display_int(info);
	*length += str_len;
	free(str);
}
