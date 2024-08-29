/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pars_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberkrou <bberkrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 07:37:03 by bberkrou          #+#    #+#             */
/*   Updated: 2024/02/21 13:25:42 by bberkrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

void	ft_init_flag(char *str, va_list args, int *lenght)
{
	t_flags	flags;

	flags.format_substr = str;
	flags.precision = -1;
	flags.width = 0;
	flags.param = 0;
	flags.zero = 0;
	flags.space_plus = 0;
	flags.square = 0;
	flags.aligne_left = 0;
	ft_manage_flags(args, flags, lenght);
}

void	ft_isolate_flags(const char *format, int len, va_list args, int *lenght)
{
	int		i;
	char	*str;

	i = 0;
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return ;
	while (i < len)
	{
		str[i] = format[i];
		i++;
	}
	str[i] = '\0';
	ft_init_flag(str, args, lenght);
	free(str);
}
