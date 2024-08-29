/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pointeur_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberkrou <bberkrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 07:51:08 by bberkrou          #+#    #+#             */
/*   Updated: 2024/02/21 10:40:23 by bberkrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

void	print_padding_pointeur(int padding_length, char pad_char, int *length)
{
	while (padding_length-- > 0)
	{
		ft_putchar_fd(pad_char, 1);
		(*length)++;
	}
}

void	ft_print_pointer(va_list args, t_flags flags, int *length)
{
	unsigned long long	ptr;
	char				*str;
	int					str_len;
	int					padding_length;

	ptr = (unsigned long long)va_arg(args, void *);
	if (!ptr)
	{
		ft_putstr_fd("(nil)", 1);
		*length += 5;
		return ;
	}
	str = ft_uitoa_base(ptr, "0123456789abcdef");
	str_len = ft_strlen(str) + 2;
	padding_length = flags.width - str_len;
	if (!flags.aligne_left && padding_length > 0)
		print_padding_pointeur(padding_length, ' ', length);
	ft_putstr_fd("0x", 1);
	*length += 2;
	ft_putstr_fd(str, 1);
	*length += str_len - 2;
	if (flags.aligne_left && padding_length > 0)
		print_padding_pointeur(padding_length, ' ', length);
	free(str);
}
