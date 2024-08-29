/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uint_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberkrou <bberkrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 08:16:30 by bberkrou          #+#    #+#             */
/*   Updated: 2024/02/21 10:40:28 by bberkrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

void	adjust_unsigned_len_and_width(t_uint_info *info)
{
	if (info->flags.precision == 0 && info->number == 0)
		info->str_len--;
	if (info->flags.precision > info->str_len)
		info->flags.width -= (info->flags.precision - info->str_len);
}

void	display_unsigned_int(t_uint_info info)
{
	if (info.flags.zero == 1 && info.flags.precision == -1)
		print_zero(info.flags.width - info.str_len, info.length);
	else if (info.flags.aligne_left != 1)
		print_padding(info.number, info.flags.width - info.str_len, \
						info.length, info.flags);
	if (info.flags.precision != -1)
		if (info.str_len < info.flags.precision)
			print_zero(info.flags.precision - info.str_len, info.length);
	if (info.flags.precision != 0 || info.number != 0)
		ft_putstr_fd(info.str, 1);
	if (info.flags.aligne_left == 1)
		print_padding(info.number, info.flags.width - info.str_len, \
						info.length, info.flags);
}

void	ft_print_unsigned_int(va_list args, t_flags flags, int *length)
{
	t_uint_info	info;

	info.number = va_arg(args, unsigned int);
	info.str = ft_utoa(info.number);
	info.str_len = ft_strlen(info.str);
	info.flags = flags;
	info.length = length;
	adjust_unsigned_len_and_width(&info);
	display_unsigned_int(info);
	*info.length += info.str_len;
	free(info.str);
}
