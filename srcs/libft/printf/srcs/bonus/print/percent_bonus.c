/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   percent_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberkrou <bberkrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 07:53:14 by bberkrou          #+#    #+#             */
/*   Updated: 2024/02/21 10:40:22 by bberkrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

void	ft_print_percent(va_list args, t_flags flags, int *length)
{
	(void)args;
	(void)flags;
	ft_putchar_fd('%', 1);
	(*length)++;
}
